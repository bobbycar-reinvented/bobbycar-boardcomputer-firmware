#pragma once

// 3rd party includes
#include <qrcode.h>

// local includes
#include "bobbydisplay.h"

uint16_t get_qrver_from_strlen(std::string_view str);

class QrDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    explicit QrDisplay(std::string_view msg);

    void initScreen() override;

    void buttonPressed(espgui::Button button) override;

private:
    std::string_view m_msg;
};
