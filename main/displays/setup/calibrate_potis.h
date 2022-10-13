#pragma once

// local includes
#include "displays/bobbydisplaywithtitle.h"

class SetupCalibratePotisDisplay : public virtual BobbyDisplayWithTitle
{
    using Base = BobbyDisplayWithTitle;
public:
    explicit SetupCalibratePotisDisplay(bool early_return = false) :
            m_early_return{early_return}
    {}

    void initScreen() override;
    void start() override;
    void update() override;
    void redraw() override;
    void stop() override;

    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;
    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;

    [[nodiscard]] std::string text() const override;

private:
    const bool m_early_return;
};
