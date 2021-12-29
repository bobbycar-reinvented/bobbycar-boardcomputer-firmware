#include "mosfetsmenu.h"

#ifdef FEATURE_MOSFETS
// 3rdparty lib includes
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "displays/menus/mainmenu.h"
#include "bobbycheckbox.h"

using namespace espgui;

MosfetsMenu::MosfetsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MOSFET0>, BobbyCheckbox, Mosfet0Accessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MOSFET1>, BobbyCheckbox, Mosfet1Accessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MOSFET2>, BobbyCheckbox, Mosfet2Accessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,    SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void MosfetsMenu::back()
{
    switchScreen<MainMenu>();
}

#endif
