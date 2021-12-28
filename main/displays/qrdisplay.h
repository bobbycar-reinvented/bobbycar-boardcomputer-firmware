#pragma once

// 3rd party includes
#include <qrcode.h>

// local includes
#include "bobbydisplay.h"

class QrDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    QrDisplay(std::string_view msg, uint8_t ver);

    void initScreen() override;

    void buttonPressed(espgui::Button button) override;

private:
    std::string_view m_msg;
    uint8_t m_ver;
};
