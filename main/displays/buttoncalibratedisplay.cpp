#include "buttoncalibratedisplay.h"

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <tftinstance.h>
#include <fmt/core.h>
#include <screenmanager.h>

// local includes
#include "newsettings.h"
#include "displays/menus/boardcomputerhardwaresettingsmenu.h"
#include "bobbyerrorhandler.h"

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

    m_finished = false;
}

void ButtonCalibrateDisplay::initScreen()
{
    Base::initScreen();

    m_labelInstruction.start();
    m_labelLeft.start();
    m_labelRight.start();
    m_labelUp.start();
    m_labelDown.start();
    m_labelEnd.start();
}

void ButtonCalibrateDisplay::update()
{
    Base::update();

    if (m_finished)
    {
        m_finished = false;

        if (auto result = configs.write_config(configs.dpadMappingLeft, m_leftButton); !result)
        {
            BobbyErrorHandler{}.errorOccured(std::move(result).error());
            return;
        }
        if (auto result = configs.write_config(configs.dpadMappingRight, m_rightButton); !result)
        {
            BobbyErrorHandler{}.errorOccured(std::move(result).error());
            return;
        }
        if (auto result = configs.write_config(configs.dpadMappingUp, m_upButton); !result)
        {
            BobbyErrorHandler{}.errorOccured(std::move(result).error());
            return;
        }
        if (auto result = configs.write_config(configs.dpadMappingDown, m_downButton); !result)
        {
            BobbyErrorHandler{}.errorOccured(std::move(result).error());
            return;
        }

        espgui::switchScreen<BoardcomputerHardwareSettingsMenu>();
    }
}

void ButtonCalibrateDisplay::redraw()
{
    Base::redraw();

    espgui::tft.setTextColor(TFT_WHITE, TFT_BLACK);

    switch (m_status)
    {
    case WaitingLeft:
        if (m_lastButton)
            m_labelInstruction.redraw("Press LEFT again");
        else
            m_labelInstruction.redraw("Press LEFT");
        break;
    case WaitingRight:
        if (m_lastButton)
            m_labelInstruction.redraw("Press RIGHT again");
        else
            m_labelInstruction.redraw("Press RIGHT");
        break;
    case WaitingUp:
        if (m_lastButton)
            m_labelInstruction.redraw("Press UP again");
        else
            m_labelInstruction.redraw("Press UP");
        break;
    case WaitingDown:
        if (m_lastButton)
            m_labelInstruction.redraw("Press DOWN again");
        else
            m_labelInstruction.redraw("Press DOWN");
        break;
    case Finished:
        m_labelInstruction.redraw("Finished");
        break;
    }

    m_labelLeft.redraw(m_status > WaitingLeft ? fmt::format("Left: {}", m_leftButton) : std::string{});
    m_labelRight.redraw(m_status > WaitingRight ? fmt::format("Right: {}", m_rightButton) : std::string{});
    m_labelUp.redraw(m_status > WaitingUp ? fmt::format("Up: {}", m_upButton) : std::string{});
    m_labelDown.redraw(m_status > WaitingDown ? fmt::format("Down: {}", m_downButton) : std::string{});

    m_labelEnd.redraw(m_status == Finished ? "Press RIGHT to save" : "");
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
            if (button == m_rightButton)
                m_finished = true;
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
