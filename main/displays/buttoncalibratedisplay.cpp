#include "buttoncalibratedisplay.h"

// esp-idf includes
#include <esp_log.h>

namespace {
constexpr const char TAG[] = "BUTTON";
} // namespace

std::string ButtonCalibrateDisplay::text() const
{
    return "Button calibrate";
}

void ButtonCalibrateDisplay::start()
{
    Base::start();

    m_oldMode = currentMode;
    currentMode = &m_mode;
    m_lastButton = std::nullopt;
    m_status = WaitingLeft;
}

void ButtonCalibrateDisplay::initScreen()
{
    Base::initScreen();

    m_label.start();
}

void ButtonCalibrateDisplay::update()
{
    Base::update();
}

void ButtonCalibrateDisplay::redraw()
{
    Base::redraw();

    switch (m_status)
    {
    case WaitingLeft:
        if (m_lastButton)
            m_label.redraw("Press LEFT again");
        else
            m_label.redraw("Press LEFT");
        break;
    case WaitingRight:
        if (m_lastButton)
            m_label.redraw("Press RIGHT again");
        else
            m_label.redraw("Press RIGHT");
        break;
    case WaitingUp:
        if (m_lastButton)
            m_label.redraw("Press UP again");
        else
            m_label.redraw("Press UP");
        break;
    case WaitingDown:
        if (m_lastButton)
            m_label.redraw("Press DOWN again");
        else
            m_label.redraw("Press DOWN");
        break;
    case Finished:
        m_label.redraw("Finished");
        break;
    }
}

void ButtonCalibrateDisplay::stop()
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

void ButtonCalibrateDisplay::rawButtonPressed(uint8_t button)
{
    //Base::rawButtonPressed(button);

    ESP_LOGI(TAG, "button=%hhu", button);

    if (!m_lastButton || *m_lastButton != button)
        m_lastButton = button;
    else
    {
        switch (m_status)
        {
        case WaitingLeft:
            m_leftButton = button;
            m_lastButton = std::nullopt;
            m_status = WaitingRight;
            break;
        case WaitingRight:
            m_rightButton = button;
            m_lastButton = std::nullopt;
            m_status = WaitingUp;
            break;
        case WaitingUp:
            m_upButton = button;
            m_lastButton = std::nullopt;
            m_status = WaitingDown;
            break;
        case WaitingDown:
            m_downButton = button;
            m_lastButton = std::nullopt;
            m_status = Finished;
            break;
        case Finished:
            break;
        }
    }
}

void ButtonCalibrateDisplay::rawButtonReleased(uint8_t button)
{
    //Base::rawButtonReleased(button);

    ESP_LOGI(TAG, "button=%hhu", button);
}

void ButtonCalibrateDisplay::buttonPressed(espgui::Button button)
{
    //Base::buttonPressed(button);
}

void ButtonCalibrateDisplay::buttonReleased(espgui::Button button)
{
    //Base::buttonReleased(button);
}
