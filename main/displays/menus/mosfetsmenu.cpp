#include "mosfetsmenu.h"

#ifdef FEATURE_MOSFETS

#include "actions/switchscreenaction.h"
#include "actions/toggleboolaction.h"
#include "checkboxicon.h"
#include "displays/menus/mainmenu.h"
#include "icons/back.h"

using namespace espgui;

MosfetsMenu::MosfetsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MOSFET0>, ToggleBoolAction, CheckboxIcon, Mosfet0Accessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MOSFET1>, ToggleBoolAction, CheckboxIcon, Mosfet1Accessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MOSFET2>, ToggleBoolAction, CheckboxIcon, Mosfet2Accessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,    SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void MosfetsMenu::back()
{
    switchScreen<MainMenu>();
}

#endif
