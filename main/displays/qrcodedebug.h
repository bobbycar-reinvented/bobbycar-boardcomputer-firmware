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
    void initScreen() override;
    void confirm() override;
    void back() override;
private:
    QRCode m_qrcode;
};
