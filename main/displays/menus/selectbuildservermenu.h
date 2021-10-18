#pragma once

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "actions/selectbuildserveraction.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"


// forward declares
namespace {
class SettingsMenu;
} // namespace

using namespace espgui;

namespace {

class SelectBuildServerMenu :
    public MenuDisplay,
    public StaticText<TEXT_SELECTBUILDSERVERMENU>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>
{
public:
    SelectBuildServerMenu() {

        auto numDisplayedServers = 0;

        for (auto index = 0; index < stringSettings.otaServers.size(); index++)
        {
            auto otaServer = stringSettings.otaServers[index];
            std::string url = otaServer.url;
            std::string name = (otaServer.name.empty()) ? url : otaServer.name;

            if (!name.empty()) {
                auto menuitem = constructMenuItem<makeComponent<MenuItem, ChangeableText, DummyAction>>();
                menuitem.setTitle(name);
                numDisplayedServers++;
            }
        }

        if (!numDisplayedServers)
        {
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NOBUILDSERVERCONFIGURED>, DummyAction>>();
        }

        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};
} // namespace
