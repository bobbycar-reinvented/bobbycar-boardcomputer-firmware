#pragma once

// 3rd party includes
#include <tftinstance.h>
#include <qrcode.h>

// local includes
#include "bobbydisplay.h"
#include "screenmanager.h"

uint16_t get_qrver_from_strlen(std::string_view str);

template<typename TMenu>
class QrDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    explicit QrDisplay(std::string_view msg) : m_msg{msg} {}

    void initScreen() override
    {
        using namespace espgui;
        QRCode qrcode;
        const auto ver = get_qrver_from_strlen(m_msg);
        uint8_t qrcodeBytes[qrcode_getBufferSize(ver)];
        qrcode_initText(&qrcode, qrcodeBytes, ver, ECC_MEDIUM, m_msg.data());

        const uint8_t multiplier = (tft.width() - 18) / qrcode.size;
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

    void buttonPressed(espgui::Button button) override
    {
        using namespace espgui;
        Base::buttonPressed(button);

        switch (button)
        {
            case espgui::Button::Left:
            case espgui::Button::Right:
                switchScreen<TMenu>();
                break;
            default:;
        }
    }

private:
    std::string_view m_msg;
};
