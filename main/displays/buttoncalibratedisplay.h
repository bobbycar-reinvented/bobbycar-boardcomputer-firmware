#pragma once

// 3rdparty lib includes
#include <displaywithtitle.h>

// local includes
#include "globals.h"
#include "modeinterface.h"
#include "modes/ignoreinputmode.h"

class ButtonCalibrateDisplay : public espgui::DisplayWithTitle
{
    using Base = espgui::DisplayWithTitle;

public:
    ButtonCalibrateDisplay() = default;
    explicit ButtonCalibrateDisplay(bool bootup) : m_bootup{bootup} {}

    std::string text() const override;
    void start() override;
    void initScreen() override;
    void update() override;
    void redraw() override;
    void stop() override;

    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;
    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;

private:
    const bool m_bootup{false};
    ModeInterface *m_oldMode;
    IgnoreInputMode m_mode{0, bobbycar::protocol::ControlType::FieldOrientedControl, bobbycar::protocol::ControlMode::Torque};
};
