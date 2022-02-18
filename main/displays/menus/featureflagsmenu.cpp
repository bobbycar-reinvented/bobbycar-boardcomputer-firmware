#include "featureflagsmenu.h"

// 3rdparty lib includes
#include <TFT_eSPI.h>
#include <actions/switchscreenaction.h>
#include <fmt/core.h>
#include <icons/back.h>
#include <strutils.h>

// local includes
#include "bobbycheckbox.h"
#include "displays/bobbypopupdisplay.h"
#include "displays/menus/settingsmenu.h"
#include "newsettings.h"
#include "taskmanager.h"

using namespace espgui;

namespace {
constexpr const char * const TAG = "FEATUREFLAGSMENU";

constexpr char TEXT_FEATUREFLAGS[] = "Feature Flags";
constexpr char TEXT_BACK[] = "Back";

class FeatureFlagMenuItem : public MenuItem, public virtual BobbyErrorHandler {
public:
    explicit FeatureFlagMenuItem(ConfiguredFeatureFlag &flag, bool isInitialized) : m_flag{flag}, m_isInitialized{isInitialized} {}
    std::string text() const override
    {
        std::string_view name = m_flag.isEnabled.nvsName();
        constexpr const std::string_view prefix = "f_";
        if (cpputils::stringStartsWith(name, prefix)) {
            name.remove_prefix(prefix.size());
        }
        std::string return_name = std::string{name};
        return_name += m_flag.isBeta() ? " (beta)" : "";
        return return_name;
    }

    int color() const override
    {
        if (m_isInitialized)
        {
            return m_flag.isBeta() ? TFT_YELLOW : TFT_GREEN;
        }
        else
        {
            return m_flag.isBeta() ? TFT_ORANGE : TFT_GREY;
        }
    }

    void triggered() override
    {
        if (auto result = m_flag.isEnabled.write(configs.nvs_handle_user, !m_flag.isEnabled.value); !result)
            errorOccured(std::move(result).error());
    }

    const MenuItemIcon *icon() const override
    {
        return m_flag.isEnabled.value ? &icons::checked : &icons::unchecked;
    }
private:
    ConfiguredFeatureFlag &m_flag;
    const bool m_isInitialized;
};

// TODO: Replace SwitchScreenAction / switchScreen with this action. Needs: BobbyPopupDisplayWithCustomExitAction => pass SwitchScreenAction<SettingsMenu> into it

class ExitFeatureFlagsMenuAction : public virtual ActionInterface {
public:
    void triggered() override {
        auto newDisplay = std::make_unique<BobbyPopupDisplay>(std::move("Please reboot if you have changed something"), std::move(espgui::currentDisplay));
        newDisplay->initOverlay();
        espgui::currentDisplay = std::move(newDisplay);
    }
};

} // namespace

FeatureFlagsMenu::FeatureFlagsMenu()
{
    configs.callForEveryFeature([&](ConfiguredFeatureFlag &feature){

        if (const auto err = checkInitializedByName(feature.getTaskName()); !err) {
                constructMenuItem<FeatureFlagMenuItem>(feature, *err);
        }
        else
            constructMenuItem<FeatureFlagMenuItem>(feature, true);
    });
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<SettingsMenu>>>();
}

std::string FeatureFlagsMenu::text() const
{
    return TEXT_FEATUREFLAGS;
}

void FeatureFlagsMenu::back()
{
    switchScreen<SettingsMenu>();
}
