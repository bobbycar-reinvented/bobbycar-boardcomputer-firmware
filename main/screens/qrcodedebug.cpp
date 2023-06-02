#include "qrcodedebug.h"

// 3rdparty lib includes
#include <fmt/core.h>
#include <tftcolors.h>
#include <tftinterface.h>

// local includes
#include "newsettings.h"
#include "screenmanager.h"

namespace bobby {

using namespace espgui;

using namespace qrcodegen;

void QrCodeDebugDisplay::redraw(espgui::TftInterface &tft)
{
    Base::redraw(tft);

    if (m_qrcode)
    {
        auto &qrcode = *m_qrcode;
        auto size = qrcode.getSize();

        for (auto y = 0; y < size; y++)
        {
            for (auto x = 0; x < size; x++)
            {
                tft.drawPixel(x + 2, y + 2, qrcode.getModule(x, y) ? espgui::TFT_BLACK : espgui::TFT_WHITE);
            }
        }

        m_qrcode.reset();
    }
}

void QrCodeDebugDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);

    switch (button)
    {
    using espgui::Button;
    case Button::Left: popScreen(); break;
    case Button::Right:
    {
        if (const auto encoded = QrCode::encodeText(fmt::format("WIFI:T:WPA;S:{};P:{};", configs.wifiApName.value(), configs.wifiApKey.value()).c_str(), QrCode::Ecc::ECC_MEDIUM); !encoded)
        {
            popScreen();
            return;
        }
        else
        {
            m_qrcode = *encoded;
        }
        break;
    }
    default:;
    }
}
} // namespace bobby
