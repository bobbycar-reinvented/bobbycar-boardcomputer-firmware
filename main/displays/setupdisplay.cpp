#include "setupdisplay.h"

// system includes
#include <esp_log.h>

// 3rdparty lib includes
#include <tftinstance.h>

using namespace espgui;
using namespace std::chrono_literals;

namespace setupdisplay {
constexpr char const InformationText[] = "Congratulations on your new\nbobbycar! This guide will help\nyou through initial setup,\ncalibrate everything and\nget you ready!";
} // setupdisplay

void SetupDisplay::start()
{
    Base::start();
    m_menu_opened_timestamp = espchrono::millis_clock::now();
}

void SetupDisplay::initScreen()
{
    Base::initScreen();
}

void SetupDisplay::update()
{
    Base::update();
}

void SetupDisplay::redraw()
{
    Base::redraw();

    if (m_current_setupStep != m_last_setupStep || initialRender)
    {
        initialRender = false;
        m_last_setupStep = m_current_setupStep;

        switch(m_current_setupStep)
        {
        case SetupStep::INFORMATION:
            drawLargeText(setupdisplay::InformationText);
            break;
        case SetupStep::BASIC_BUTTONS:
            clearLargeText();
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
}

void SetupDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);
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

void SetupDisplay::clearLargeText()
{
    tft.fillRect(0, 50, tft.width(), tft.height()-50, TFT_BLACK);
}
