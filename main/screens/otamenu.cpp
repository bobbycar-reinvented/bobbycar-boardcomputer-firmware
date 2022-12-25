#include "otamenu.h"

// 3rdparty lib includes
#include <actioninterface.h>
#include <actions/dummyaction.h>
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <icons/back.h>

// local includes
#include "screens/selectbuildserverbranch.h"
#include "screens/selectbuildservermenu.h"
#include "screens/selectotabuildmenu.h"
#include "screens/updatedisplay.h"
#include "icons/presets.h"
#include "icons/update.h"

namespace bobby {

namespace {
constexpr char TEXT_UPDATE[] = "Update";
constexpr char TEXT_UPDATENOW[] = "Update now";
constexpr char TEXT_SELECTBUILD[] = "Select build";
constexpr char TEXT_SELECT_BRANCH[] = "Select Branch";
constexpr char TEXT_SELECTBUILDSERVERMENU[] = "Select Buildserver";
constexpr char TEXT_BACK[] = "Back";
} // namespace

OtaMenu::OtaMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECTBUILD>,             PushScreenAction<SelectBuildMenu>, StaticMenuItemIcon<&bobbyicons::presets>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECT_BRANCH>,           PushScreenAction<SelectBuildserverBranchMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UPDATENOW>,               PushScreenAction<UpdateDisplay>, StaticMenuItemIcon<&bobbyicons::update>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECTBUILDSERVERMENU>,   PushScreenAction<SelectBuildServerMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                    PopScreenAction, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string OtaMenu::text() const
{
    return TEXT_UPDATE;
}

void OtaMenu::back()
{
    espgui::popScreen();
}
} // namespace bobby
