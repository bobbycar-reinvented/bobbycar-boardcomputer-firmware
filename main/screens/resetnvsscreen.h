#pragma once

// 3rdparty lib includes
#include <tftinterface.h>

// local includes
#include "guihelpers/bobbydisplaywithtitle.h"

namespace bobby {
class ResetNVSScreen : public BobbyDisplayWithTitle
{
    using Base = BobbyDisplayWithTitle;

public:
    void initScreen(espgui::TftInterface &tft) override;

    std::string title() const override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
} // namespace bobby
