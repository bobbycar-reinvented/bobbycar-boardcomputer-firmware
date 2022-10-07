#pragma once

// system includes
#include <string_view>
#include <optional>

// 3rdparty lib includes
#include <actioninterface.h>
#include <espchrono.h>
#include <screenmanager.h>
#include <tftinstance.h>
#include <widgets/progressbar.h>

// local includes
#include "bobbydisplaywithtitle.h"
#include "bobbytypesafeenum.h"
#include "modeinterface.h"
#include "modes/ignoreinputmode.h"

#define SetupStepValues(x) \
    x(INFORMATION)         \
    x(BASIC_BUTTONS)       \
    x(CALIBRATE_POTIS)     \
    x(ASK_SETUP_CLOUDS)    \
    x(SETUP_CLOUD)         \
    x(ASK_CALIBRATE_OTHER_BUTTONS) /*add pushScreen<Name> after switchScreen<StatusDisplay>*/ \
    x(FINAL_INFORMATION)

DECLARE_BOBBYTYPESAFE_ENUM(SetupStep, : uint8_t, SetupStepValues);

namespace setupdisplay {
enum CurrentButton : int8_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FINISHED
};

enum CurrentCloudSelect : uint8_t
{
    CLOUD_ENABLE,
    CLOUD_URL,
    CLOUD_KEY,
    DONE,
    _LAST,
};
namespace {
constexpr char const TEXT_CLOUDURL[] = "Cloud URL";
constexpr char const TEXT_CLOUDKEY[] = "Cloud Key";
} // namespace
}

class SetupDisplay : public BobbyDisplayWithTitle
{
    using Base = BobbyDisplayWithTitle;

public:
    explicit SetupDisplay(SetupStep initialStep = SetupStep::INFORMATION, bool early_return = false) :
            m_current_setupStep{initialStep},
            m_last_setupStep{initialStep},
            m_early_return{early_return}
    {}

    void start() override;
    void initScreen() override;
    void redraw() override;
    void update() override;
    void stop() override;

    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;
    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;

    [[nodiscard]] std::string text() const override;
private:
    // general
    SetupStep m_current_setupStep;
    SetupStep m_last_setupStep;
    espchrono::millis_clock::time_point m_menu_opened_timestamp;
    bool m_initialRender{true};
    const bool m_early_return;
    espgui::ProgressBar m_init_text_progressbar{10, espgui::tft.height()/2, espgui::tft.width()-20, 30, 0, 100};

    static void drawLargeText(const std::string&& text);
    static void clearArea();
    void drawButtons(setupdisplay::CurrentButton button);
    void nextStep();

    // button calibration
    ModeInterface *m_oldMode;
    IgnoreInputMode m_mode{0, bobbycar::protocol::ControlType::FieldOrientedControl, bobbycar::protocol::ControlMode::Torque};

    std::optional<uint8_t> m_lastButton;

    setupdisplay::CurrentButton m_button_cal_status;
    uint8_t m_leftButton, m_rightButton, m_upButton, m_downButton;
    bool m_button_cal_finished;
    void saveButtons();

    // poti calibration
    // ToDo: Implement this

    // cloud
    void drawWebsocketCloud() const;
    setupdisplay::CurrentCloudSelect m_cloud_selected_item{setupdisplay::CLOUD_ENABLE};
};

class PushSetupDisplayAction : public virtual espgui::ActionInterface {
public:
    explicit PushSetupDisplayAction(SetupStep setupStep, bool early_return = false) :
        m_setupStep{setupStep},
        m_early_return{early_return}
    {}

    void triggered() override
    {
        espgui::pushScreen<SetupDisplay>(m_setupStep, m_early_return);
    }
private:
    const SetupStep m_setupStep;
    const bool m_early_return;
};
