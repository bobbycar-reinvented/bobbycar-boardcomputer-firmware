#include "powersupplydisplay.h"

// 3rdparty lib includes
#include <tftinstance.h>
#include <screenmanager.h>
#include "actions/switchscreenaction.h"

// local includes
#include "globals.h"
#include "displays/menus/mainmenu.h"

#if defined(FEATURE_CAN) && defined(FEATURE_POWERSUPPLY)
void PowerSupplyDisplay::initScreen()
{
    espgui::tft.fillScreen(TFT_BLACK);
    espgui::tft.setTextColor(TFT_WHITE, TFT_BLACK);

    espgui::tft.setTextFont(4);

    espgui::tft.drawString("Voltage:", 0, m_voltageLabel.y());
    m_voltageLabel.start();
    espgui::tft.drawString("Current:", 0, m_currentLabel.y());
    m_currentLabel.start();
}

void PowerSupplyDisplay::redraw()
{
    m_voltageLabel.redraw(std::to_string(50.4) + 'V');
    m_currentLabel.redraw(std::to_string(15.1) + 'A');
}

void PowerSupplyDisplay::confirm()
{
    // TODO
}

void PowerSupplyDisplay::back()
{
    espgui::switchScreen<MainMenu>();
}

void PowerSupplyDisplay::rotate(int offset)
{
    // TODO
}
#endif
