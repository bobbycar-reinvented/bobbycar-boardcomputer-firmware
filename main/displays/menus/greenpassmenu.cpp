#include "greenpassmenu.h"

// local includes
#include "actions/switchscreenaction.h"
#include "actions/qraction.h"
#include "displays/menus/mainmenu.h"
#include "displays/qrdisplay.h"
#include "displays/qrimportdisplay.h"
#include "icons/back.h"

using namespace espgui;

GreenPassMenu::GreenPassMenu()
{
    constructMenuItem<makeComponentArgs<MenuItem, SwitchQrDisplayAction, StaticText<TEXT_SHOWCERT>>>(qraction::QrMenu{.message="CORONA_PASS", .ver=15});
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ADDCERT>, SwitchScreenAction<QrImportDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void GreenPassMenu::back()
{
    switchScreen<MainMenu>();
}
