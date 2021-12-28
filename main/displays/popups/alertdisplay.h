#pragma once

// system includes
#include <memory>

// local includes
#include "displays/bobbydisplay.h"

class AlertDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    AlertDisplay(std::string &&message, std::unique_ptr<Display> &&lastDisplay);

    //void start() override;
    void initScreen() override;
    //void update() override;
    //void redraw() override;
    //void stop() override;

    void buttonPressed(espgui::Button button) override;

    void initOverlay();
    void closeOverlay();

private:
    std::string m_message;
    std::unique_ptr<Display> m_lastDisplay;
};
