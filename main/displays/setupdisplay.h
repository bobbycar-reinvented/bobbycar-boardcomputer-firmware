#pragma once

// system includes
#include <string_view>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "bobbydisplaywithtitle.h"
#include "bobbytypesafeenum.h"

#define SetupStepValues(x) \
    x(INFORMATION)         \
    x(BASIC_BUTTONS)       \
    x(CALIBRATE_POTIS)     \
    x(ASK_SETUP_CLOUDS)    \
    x(SETUP_CLOUD)         \
    x(SETUP_UDPCLOUD)      \
    x(ASK_CALIBRATE_OTHER_BUTTONS) /*add pushScreen<Name> after switchScreen<StatusDisplay>*/ \
    x(FINAL_INFORMATION)

DECLARE_BOBBYTYPESAFE_ENUM(SetupStep, : uint8_t, SetupStepValues);

class SetupDisplay : public BobbyDisplayWithTitle
{
    using Base = BobbyDisplayWithTitle;
public:
    explicit SetupDisplay(SetupStep initialStep = SetupStep::INFORMATION) :
        m_current_setupStep{initialStep},
        m_last_setupStep{initialStep}
    {}

    void start() override;
    void initScreen() override;
    void redraw() override;
    void update() override;
    void stop() override;

    void buttonPressed(espgui::Button button) override;

    std::string text() const override;
private:
    SetupStep m_current_setupStep;
    SetupStep m_last_setupStep;
    espchrono::millis_clock::time_point m_menu_opened_timestamp;
    bool initialRender{true};

    static void drawLargeText(const std::string&& text);
    static void clearLargeText();
    void nextStep();
};
