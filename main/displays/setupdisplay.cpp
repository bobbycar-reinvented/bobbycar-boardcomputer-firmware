#include "setupdisplay.h"

// system includes
#include <esp_log.h>

// 3rdparty lib includes
#include <tftinstance.h>

// local includes
#include "globals.h"

using namespace espgui;
using namespace std::chrono_literals;

namespace setupdisplay {
constexpr char const InformationText[] = "Congratulations on your new\nbobbycar! This guide will help\nyou through initial setup,\ncalibrate everything and\nget you ready!";
constexpr char const ButtonText[] = "Please press the highlighted\n buttons!";
} // setupdisplay

namespace {
constexpr const char * const TAG = "SETUPDISPLAY";
} // namespace

void SetupDisplay::start()
{
    Base::start();
    m_menu_opened_timestamp = espchrono::millis_clock::now();

    m_oldMode = currentMode;
    currentMode = &m_mode;
    m_lastButton = std::nullopt;
    m_button_cal_status = setupdisplay::LEFT;
    m_button_cal_finished = false;
}

void SetupDisplay::initScreen()
{
    Base::initScreen();
}

void SetupDisplay::update()
{
    Base::update();

    switch(m_current_setupStep)
    {
    case SetupStep::BASIC_BUTTONS:
        break;
    default:;
    }
}

void SetupDisplay::redraw()
{
    Base::redraw();

    if (m_current_setupStep != m_last_setupStep || m_initialRender)
    {
        m_initialRender = false;
        m_last_setupStep = m_current_setupStep;

        switch(m_current_setupStep)
        {
        case SetupStep::INFORMATION:
            drawLargeText(setupdisplay::InformationText);
            break;
        case SetupStep::BASIC_BUTTONS:
            clearArea();
            drawLargeText(setupdisplay::ButtonText);
            drawButtons(m_button_cal_status);
            break;
        case SetupStep::CALIBRATE_POTIS:
            break;
        case SetupStep::ASK_SETUP_CLOUDS:
            break;
        case SetupStep::SETUP_CLOUD:
            break;
        case SetupStep::SETUP_UDPCLOUD:
            break;
        case SetupStep::ASK_CALIBRATE_OTHER_BUTTONS:
            break;
        case SetupStep::FINAL_INFORMATION:
            break;
        }
    }

    if (m_current_setupStep == SetupStep::INFORMATION && espchrono::ago(m_menu_opened_timestamp) > 5s)
    {
        nextStep();
    }
}

void SetupDisplay::stop()
{
    Base::stop();

    if (currentMode == &m_mode)
    {
        // to avoid crash after deconstruction
        m_mode.stop();
        lastMode = nullptr;

        currentMode = m_oldMode;
    }
}

void SetupDisplay::buttonPressed(espgui::Button button)
{
    if (m_current_setupStep == SetupStep::BASIC_BUTTONS)
    {
        return;
    }

    Base::buttonPressed(button);
}

void SetupDisplay::buttonReleased(espgui::Button button)
{
    if (m_current_setupStep == SetupStep::BASIC_BUTTONS)
    {
        return;
    }

    Base::buttonReleased(button);
}

void SetupDisplay::rawButtonPressed(uint8_t button)
{
    Base::rawButtonPressed(button);

    if (m_current_setupStep != SetupStep::BASIC_BUTTONS)
    {
        return;
    }

    if (m_button_cal_status == setupdisplay::FINISHED)
    {
        if (button == m_rightButton)
        {
            ESP_LOGI(TAG, "correct button");
            m_button_cal_finished = true;
        }
        else
            ESP_LOGI(TAG, "wrong button");
    }
    else if (!m_lastButton || *m_lastButton != button)
        m_lastButton = button;
    else
    {
        switch (m_button_cal_status)
        {
        case setupdisplay::LEFT:
            m_leftButton = button;
            m_lastButton = std::nullopt;
            m_button_cal_status = setupdisplay::RIGHT;
            break;
        case setupdisplay::RIGHT:
            m_rightButton = button;
            m_lastButton = std::nullopt;
            m_button_cal_status = setupdisplay::UP;
            break;
        case setupdisplay::UP:
            m_upButton = button;
            m_lastButton = std::nullopt;
            m_button_cal_status = setupdisplay::DOWN;
            break;
        case setupdisplay::DOWN:
            m_downButton = button;
            m_lastButton = std::nullopt;
            m_button_cal_status = setupdisplay::FINISHED;
            break;
        case setupdisplay::FINISHED:;
        }
    }

    drawButtons(m_button_cal_status);
}

void SetupDisplay::saveButtons()
{

}

void SetupDisplay::rawButtonReleased(uint8_t button)
{
    // Base::rawButtonReleased(button);
}

std::string SetupDisplay::text() const
{
    switch (m_current_setupStep)
    {
    case SetupStep::INFORMATION:
        return "First Steps";
    case SetupStep::BASIC_BUTTONS:
        return "Calibrate Buttons";
    case SetupStep::CALIBRATE_POTIS:
        return "Calibrate Potis";
    case SetupStep::ASK_SETUP_CLOUDS:
        return "Cloud Setup";
    case SetupStep::SETUP_CLOUD:
        return "WebSocket Cloud";
    case SetupStep::SETUP_UDPCLOUD:
        return "UDP Cloud";
    case SetupStep::ASK_CALIBRATE_OTHER_BUTTONS:
        return "Other Buttons";
    case SetupStep::FINAL_INFORMATION:
        return "All done!";
    }
    return {};
}

void SetupDisplay::drawLargeText(const std::string&& text)
{
    const auto topMargin = 50;
    const uint8_t leftMargin = 8;
    const auto rightMargin = leftMargin;
    const auto bottomMargin = leftMargin;

    int x = leftMargin + 5;
    int y = topMargin + 5;

    tft.setTextColor(TFT_WHITE);

    for (char c : text)
    {
        if (c == '\n' || x > tft.width() - rightMargin - 10)
        {
            x = leftMargin + 5;
            y += tft.fontHeight(2);
        }

        if (c != '\n')
        {
            const auto addedWidth = tft.drawChar(tft.decodeUTF8(c), x, y, 2);
            x += addedWidth;
        }

        if (y >= tft.height() - bottomMargin)
            break;
    }
}

void SetupDisplay::nextStep()
{
    ESP_LOGI("SetupDisplay", "nextStep (%s)", toString(m_current_setupStep).c_str());
    switch(m_current_setupStep)
    {
    case SetupStep::INFORMATION:
        m_current_setupStep = SetupStep::BASIC_BUTTONS;
        break;
    case SetupStep::BASIC_BUTTONS:
        m_current_setupStep = SetupStep::CALIBRATE_POTIS;
        break;
    case SetupStep::CALIBRATE_POTIS:
        m_current_setupStep = SetupStep::ASK_SETUP_CLOUDS;
        break;
    case SetupStep::ASK_SETUP_CLOUDS:
        m_current_setupStep = SetupStep::SETUP_CLOUD;
        break;
    case SetupStep::SETUP_CLOUD:
        m_current_setupStep = SetupStep::SETUP_UDPCLOUD;
        break;
    case SetupStep::SETUP_UDPCLOUD:
        m_current_setupStep = SetupStep::ASK_CALIBRATE_OTHER_BUTTONS;
        break;
    case SetupStep::ASK_CALIBRATE_OTHER_BUTTONS:
        m_current_setupStep = SetupStep::FINAL_INFORMATION;
        break;
    case SetupStep::FINAL_INFORMATION:
        break;
    }
    ESP_LOGI("SetupDisplay", "nextStep after (%s)", toString(m_current_setupStep).c_str());
}

void SetupDisplay::clearArea()
{
    tft.fillRect(0, 50, tft.width(), tft.height()-50, TFT_BLACK);
}

void SetupDisplay::drawButtons(setupdisplay::CurrentButton button)
{
    const int16_t x_mid = tft.width() / 2;
    const int16_t y_mid = tft.height() / 2;

    const auto offset = 40;
    const auto radius = 15;
    const auto subtract = 2;

    const auto up_x = x_mid;
    const auto up_y = y_mid - offset;

    const auto down_x = x_mid;
    const auto down_y = y_mid + offset;

    const auto left_x = x_mid - offset;
    const auto left_y = y_mid;

    const auto right_x = x_mid + offset;
    const auto right_y = y_mid;

    tft.fillCircle(up_x,    up_y,    radius-subtract, TFT_BLACK);
    tft.fillCircle(down_x,  down_y,  radius-subtract, TFT_BLACK);
    tft.fillCircle(left_x,  left_y,  radius-subtract, TFT_BLACK);
    tft.fillCircle(right_x, right_y, radius-subtract, TFT_BLACK);

    tft.drawCircle(up_x,    up_y,    radius, TFT_WHITE);
    tft.drawCircle(down_x,  down_y,  radius, TFT_WHITE);
    tft.drawCircle(left_x,  left_y,  radius, TFT_WHITE);
    tft.drawCircle(right_x, right_y, radius, TFT_WHITE);

    switch(button)
    {
    case setupdisplay::UP:
        tft.fillCircle(up_x, up_y, radius-subtract, m_lastButton ? TFT_YELLOW : TFT_WHITE);
        break;
    case setupdisplay::DOWN:
        tft.fillCircle(down_x,  down_y,  radius-subtract, m_lastButton ? TFT_YELLOW : TFT_WHITE);
        break;
    case setupdisplay::LEFT:
        tft.fillCircle(left_x,  left_y,  radius-subtract, m_lastButton ? TFT_YELLOW : TFT_WHITE);
        break;
    case setupdisplay::RIGHT:
        tft.fillCircle(right_x, right_y, radius-subtract, m_lastButton ? TFT_YELLOW : TFT_WHITE);
        break;
    default:;
    }

    if (m_button_cal_status == setupdisplay::FINISHED)
    {
        tft.fillCircle(right_x, right_y, radius-subtract, TFT_GREEN);
    }
}
