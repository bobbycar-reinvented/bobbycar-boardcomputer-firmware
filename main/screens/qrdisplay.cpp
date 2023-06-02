#include "qrdisplay.h"

// system includes
#include <cmath>

// 3rd party includes
#include <qrcodegen.hpp>
#include <screenmanager.h>
#include <tftinterface.h>
#include <tftcolors.h>

// local includes
#include "guihelpers/bobbydisplay.h"
#include "newsettings.h"

using namespace qrcodegen;

namespace bobby {

QrDisplay::QrDisplay(std::string_view msg) : m_msg{msg} {}

void QrDisplay::initScreen(espgui::TftInterface &tft)
{
    using namespace espgui;

    if (const auto encoded = QrCode::encodeText(m_msg.data(), QrCode::Ecc::ECC_MEDIUM); !encoded)
    {
        popScreen();
        return;
    }
    else
    {
        const QrCode &qrcode = *encoded;
        // 10px border
        const auto size = qrcode.getSize();
        const auto size_with_border = size + 10;

        // 320x240 tft.width() x tft.height()
        // calculate multiplier by seeing how many pixels would fit. use float, round down, then cast to int
        const auto multiplier = static_cast<int>(std::floor(tft.width() / size_with_border));

        // center the qr code
        const auto x_offset = (tft.width() - (size * multiplier)) / 2;
        const auto y_offset = (tft.height() - (size * multiplier)) / 2;

        // clear screen
        tft.fillScreen(TFT_WHITE);

        // draw qr code
        for (auto y = 0; y < size; y++)
        {
            for (auto x = 0; x < size; x++)
            {
                tft.fillRect(x_offset + (x * multiplier), y_offset + (y * multiplier), multiplier, multiplier, qrcode.getModule(x, y) ? TFT_BLACK : TFT_WHITE);
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
        espgui::popScreen();
        break;
    default:;
    }
}

void QrDisplay::start()
{
    Base::start();
    m_oldBrightness = configs.boardcomputerHardware.display_brightness.value();
    configs.write_config(configs.boardcomputerHardware.display_brightness, 50);
}

void QrDisplay::stop()
{
    Base::stop();
    configs.write_config(configs.boardcomputerHardware.display_brightness, m_oldBrightness);
}

} // namespace bobby
