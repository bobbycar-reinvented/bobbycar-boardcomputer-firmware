#include "qrcodedebug.h"

#include <fmt/core.h>
#include <tftinstance.h>

#include "displays/menus/debugmenu.h"
#include "globals.h"
#include "screenmanager.h"

using namespace espgui;

QrCodeDebugDisplay::QrCodeDebugDisplay()
{
}

void QrCodeDebugDisplay::initScreen()
{
    Base::initScreen();
}

void QrCodeDebugDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);

    switch (button)
    {
    using espgui::Button;
    case Button::Left:
        switchScreen<DebugMenu>();
        break;
    case Button::Right:
    {
        uint8_t qrcodeBytes[qrcode_getBufferSize(7)];
        qrcode_initText(&m_qrcode, qrcodeBytes, 7, ECC_MEDIUM, fmt::format("WIFI:T:WPA;S:{};P:{};", deviceName, stringSettings.ap_password).c_str());

        for (uint8_t y = 0; y < m_qrcode.size; y++) {
            for (uint8_t x = 0; x < m_qrcode.size; x++) {
                if (qrcode_getModule(&m_qrcode, x, y))
                {
                    tft.drawPixel(x+2,y+2, TFT_BLACK);
                } else {
                    tft.drawPixel(x+2,y+2, TFT_WHITE);
                }
            }
        }
        break;
    }
    default:;
    }
}
