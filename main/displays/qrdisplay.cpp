#include "qrdisplay.h"

// 3rd party libs
#include <tftinstance.h>
#include <screenmanager.h>

// local includes
#include "displays/menus/greenpassmenu.h"

using namespace espgui;

QrDisplay::QrDisplay(std::string_view msg) :
    m_msg{msg}
{
}

uint16_t get_qrver_from_strlen(std::string_view str)
{
    // alpha numeric, ECC Level M
    // version 1-40
    uint32_t len = str.length();
    if (len <= 20)
        return 1;
    else if (len <= 38)
        return 2;
    else if (len <= 61)
        return 3;
    else if (len <= 90)
        return 4;
    else if (len <= 122)
        return 5;
    else if (len <= 154)
        return 6;
    else if (len <= 178)
        return 7;
    else if (len <= 221)
        return 8;
    else if (len <= 262)
        return 9;
    else if (len <= 311)
        return 10;
    else if (len <= 366)
        return 11;
    else if (len <= 419)
        return 12;
    else if (len <= 483)
        return 13;
    else if (len <= 528)
        return 14;
    else if (len <= 600)
        return 15;
    else if (len <= 656)
        return 16;
    else if (len <= 734)
        return 17;
    else if (len <= 816)
        return 18;
    else if (len <= 909)
        return 19;
    else if (len <= 970)
        return 20;
    else if (len <= 1035)
        return 21;
    else if (len <= 1134)
        return 22;
    else if (len <= 1248)
        return 23;
    else if (len <= 1326)
        return 24;
    else if (len <= 1451)
        return 25;
    else if (len <= 1542)
        return 26;
    else if (len <= 1637)
        return 27;
    else if (len <= 1732)
        return 28;
    else if (len <= 1839)
        return 29;
    else if (len <= 1994)
        return 30;
    else if (len <= 2113)
        return 31;
    else if (len <= 2238)
        return 32;
    else if (len <= 2369)
        return 33;
    else if (len <= 2506)
        return 34;
    else if (len <= 2632)
        return 35;
    else if (len <= 2780)
        return 36;
    else if (len <= 2894)
        return 37;
    else if (len <= 3054)
        return 38;
    else if (len <= 3220)
        return 39;
    else
        return 40;
}

void QrDisplay::initScreen()
{
    QRCode qrcode;
    const auto ver = get_qrver_from_strlen(m_msg);
    uint8_t qrcodeBytes[qrcode_getBufferSize(ver)];
    qrcode_initText(&qrcode, qrcodeBytes, ver, ECC_MEDIUM, m_msg.data());

    const uint8_t multiplier = (tft.width() - 9) / qrcode.size;
    const uint8_t x_offset = (tft.width() - qrcode.size * multiplier) / 2;
    const uint8_t y_offset = (tft.height() - qrcode.size * multiplier) / 2;

    tft.fillScreen(TFT_WHITE);

    for (uint8_t y = 0; y < qrcode.size; y++) {
        for (uint8_t x = 0; x < qrcode.size; x++) {
            if (qrcode_getModule(&qrcode, x, y))
            {
                tft.fillRect(x*multiplier+x_offset,y*multiplier+y_offset, multiplier, multiplier, TFT_BLACK);
            } else {
                tft.fillRect(x*multiplier+x_offset,y*multiplier+y_offset, multiplier, multiplier, TFT_WHITE);
            }
        }
    }
}

void QrDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);

    switch (button)
    {
    case espgui::Button::Left:
    case espgui::Button::Right:
        switchScreen<GreenPassMenu>();
        break;
    default:;
    }
}
