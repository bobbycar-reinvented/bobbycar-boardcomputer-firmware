#include "otamenu.h"

// esp-idf includes
#include <esp_ota_ops.h>

// 3rdparty lib includes
#include <actions/dummyaction.h>
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <textinterface.h>

// local includes
#include "actions/switchapppartitionaction.h"
#include "icons/back.h"
#include "icons/back_grey.h"
#include "icons/presets.h"
#include "icons/presets_grey.h"
#include "icons/update.h"
#include "icons/update_grey.h"
#include "ota.h"
#include "screens/selectbuildserverbranch.h"
#include "screens/selectbuildservermenu.h"
#include "screens/selectotabuildmenu.h"
#include "screens/updatedisplay.h"

namespace bobby {

namespace {
constexpr char TEXT_UPDATE[] = "Update";
constexpr char TEXT_UPDATENOW[] = "Update now";
constexpr char TEXT_SELECTBUILD[] = "Select build";
constexpr char TEXT_SELECT_BRANCH[] = "Select Branch";
constexpr char TEXT_SELECTBUILDSERVERMENU[] = "Select Buildserver";
constexpr char TEXT_SWITCHAPPPARTITION[] = "Switch app partition";
constexpr char TEXT_BACK[] = "Back";

class CurrentAppPartitionText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        if (const auto desc = esp_ota_get_app_description(); desc)
            return fmt::format("&s{}", desc->version);
        else
            return "&2Unknown";
    }
};

class OtherAppPartitionText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        if (const auto desc = ota::otherAppDesc; desc)
            return fmt::format("&s{}", desc->version);
        else
            return "&2Unknown";
    }
};
} // namespace

OtaMenu::OtaMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECTBUILD>,             PushScreenAction<SelectBuildMenu>, StaticMenuItemIcon<&bobbyicons::presets, &bobbyicons::presets_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECT_BRANCH>,           PushScreenAction<SelectBuildserverBranchMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UPDATENOW>,               PushScreenAction<UpdateDisplay>, StaticMenuItemIcon<&bobbyicons::update, &bobbyicons::update_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECTBUILDSERVERMENU>,   PushScreenAction<SelectBuildServerMenu>>>();
    constructMenuItem<makeComponent<MenuItem, EmptyText,                                DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SWITCHAPPPARTITION>,      SwitchAppPartitionAction>>();
    constructMenuItem<makeComponent<MenuItem, CurrentAppPartitionText,                  DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, OtherAppPartitionText,                    DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, EmptyText,                                DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                    PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
}

std::string OtaMenu::title() const
{
    return TEXT_UPDATE;
}

void OtaMenu::back()
{
    espgui::popScreen();
}
} // namespace bobby
