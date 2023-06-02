#pragma once

// local includes
#include "guihelpers/bobbydisplay.h"

namespace bobby {

class QrDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    explicit QrDisplay(std::string_view msg);

    void start() override;

    void stop() override;

    void initScreen(espgui::TftInterface &tft) override;

    void buttonPressed(espgui::Button button) override;

private:
    uint8_t m_oldBrightness{0};
    std::string_view m_msg;
};
} // namespace bobby
