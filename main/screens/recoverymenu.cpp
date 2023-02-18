#include "recoverymenu.h"

// 3rdparty lib includes
#include <actions/pushscreenaction.h>
#include <menuitem.h>

// local includes
#include "actions/dummyaction.h"
#include "actions/resetnvsaction.h"
#include "guihelpers/bobbycheckbox.h"
#include "guihelpers/bobbyerrorhandler.h"
#include "icons/checked.h"
#include "icons/info.h"
#include "icons/info_grey.h"
#include "icons/reboot.h"
#include "icons/reboot_grey.h"
#include "icons/unchecked.h"
#include "newsettings.h"
#include "screens/rebootscreen.h"
#include "texthelpers/esptexthelpers.h"

namespace bobby {

namespace {
constexpr char TEXT_RESET_NVS[] = "Reset NVS";
constexpr char TEXT_REBOOT[] = "Reboot";
}

class BasicFeatureFlagMenuItem : public espgui::MenuItem
{
public:
    BasicFeatureFlagMenuItem(ConfiguredFeatureFlag &flag) :
        m_flag{flag}
    {}

    std::string text() const override
    {
        return m_flag.isEnabled.nvsName();
    }

    void triggered() override
    {
        if (auto result = m_flag.isEnabled.write(configs.nvs_handle_user, !m_flag.isEnabled.value()); !result)
            BobbyErrorHandler{}.errorOccurred(std::move(result).error());
    }

    const espgui::MenuItemIcon *icon(bool selected) const override
    {
        if (selected)
            return m_flag.isEnabled.value() ? &bobbyicons::checked_grey : &bobbyicons::unchecked_grey;
        else
            return m_flag.isEnabled.value() ? &bobbyicons::checked : &bobbyicons::unchecked;
    }
private:
    ConfiguredFeatureFlag &m_flag;
};

RecoveryMenu::RecoveryMenu()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem, LastRebootReasonText, StaticFont<2>, DisabledColor, DummyAction>>();

    configs.callForEveryFeature([&](ConfiguredFeatureFlag &feature){
        constructMenuItem<BasicFeatureFlagMenuItem>(feature);
        return false;
    });
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_RESET_NVS>, ResetNVSAction, StaticMenuItemIcon<&bobbyicons::info, &bobbyicons::info_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_REBOOT>, PushScreenAction<RebootScreen>, StaticMenuItemIcon<&bobbyicons::reboot, &bobbyicons::reboot_grey>>>();
}

std::string RecoveryMenu::title() const
{
    return "Recovery Menu";
}
} // namespace bobby
