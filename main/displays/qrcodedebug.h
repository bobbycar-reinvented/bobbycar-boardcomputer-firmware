#pragma once

// 3rdparty lib includes
#include <display.h>
#include <qrcode.h>

class QrCodeDebugDisplay :
    public espgui::Display
{
    using Base = espgui::Display;
public:
    QrCodeDebugDisplay();
    // std::string text() const override;
    void initScreen() override;
    void confirm() override;
    void back() override;
    void rotate(int offset) override;
private:
    qrcode::QRcode m_qrcode{};
    uint8_t m_mult{2};
};
