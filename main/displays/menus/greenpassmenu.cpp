#include "greenpassmenu.h"

#include <actioninterface.h>

// local includes
#include "actions/switchscreenaction.h"
#include "displays/menus/mainmenu.h"
#include "icons/back.h"

using namespace espgui;

namespace greenpassmenu {
bool showingQRCode{false};
} // namespace

void GreenPassMenu::ShowCertAction::triggered() {
    greenpassmenu::showingQRCode = true;
    m_qrcode.init();
    m_qrcode.createScaleToFit("");
}

GreenPassMenu::GreenPassMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SHOWCERT>, ShowCertAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void GreenPassMenu::initScreen()
{
    Base::initScreen();
    greenpassmenu::showingQRCode = false;
}

void GreenPassMenu::rotate(int offset)
{
    if (greenpassmenu::showingQRCode)
        GreenPassMenu::initScreen();
    Base::rotate(offset);
}

void GreenPassMenu::back()
{
    if (greenpassmenu::showingQRCode)
    {
        GreenPassMenu::initScreen();
    }
    else
        switchScreen<MainMenu>();
}
