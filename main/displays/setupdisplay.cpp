#include "setupdisplay.h"

// system includes
#include <esp_log.h>

// 3rdparty lib includes
#include <actions/popscreenaction.h>
#include <changevaluedisplay_string.h>
#include <fmt/core.h>

// local includes
#include "accessors/settingsaccessors.h"
#include "bobbychangevaluedisplay.h"
#include "bobbyerrorhandler.h"
#include "displays/menus/extrabuttoncalibratemenu.h"
#include "displays/statusdisplay.h"
#include "globals.h"
#include "taskmanager.h"

using namespace espgui;
using namespace std::chrono_literals;

namespace setupdisplay {
constexpr char const InformationText[] = "Congratulations on your new\nbobbycar! This guide will help\nyou through initial setup,\ncalibrate everything and\nget you ready!";
constexpr char const ButtonText[] = "Please press the highlighted\n buttons!";
constexpr char const AskCloudText[] = "Do you want to setup cloud?\nWith this, you will be able\nto send data to graphana,\nremote control things like Buttons\nand NVS and more!\n\nPress LEFT to skip cloud.\nPress RIGHT to setup cloud.";
constexpr char const AskSetupOtherButtonsText[] = "Do you want to setup other\nbuttons?\n(Blinker, Profile Buttons, etc.)\n\nPress LEFT to skip other buttons.\nPress RIGHT to setup buttons.";
constexpr char const FinalInformationText[] = "Setup is done!\nIf cloud is setup, go to\nhttps://service.bobbycar.cloud/\nand register this bobbycar!\nThis is also used\nto setup udp cloud.\nPress any button to exit.";
constexpr const char * const TAG = "SETUPDISPLAY";
} // setupdisplay

using CloudURLChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<std::string>,
    espgui::StaticText<setupdisplay::TEXT_CLOUDURL>,
    CloudURLAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using CloudKeyChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<std::string>,
    espgui::StaticText<setupdisplay::TEXT_CLOUDKEY>,
    CloudKeyAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

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

    switch (m_current_setupStep)
    {
    case SetupStep::SETUP_CLOUD:
        drawWebsocketCloud();
        break;
    default:;
    }
}

void SetupDisplay::update()
{
    Base::update();

    switch(m_current_setupStep)
    {
    case SetupStep::BASIC_BUTTONS:
        if (m_button_cal_finished)
        {
            m_button_cal_finished = false;
            saveButtons();
            nextStep();
        }
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

        clearArea();

        switch(m_current_setupStep)
        {
        case SetupStep::INFORMATION:
            drawLargeText(setupdisplay::InformationText);
            m_init_text_progressbar.start();
            break;
        case SetupStep::BASIC_BUTTONS:
            drawLargeText(setupdisplay::ButtonText);
            drawButtons(m_button_cal_status);
            break;
        case SetupStep::CALIBRATE_POTIS:
            // ToDo
            break;
        case SetupStep::ASK_SETUP_CLOUDS:
            drawLargeText(setupdisplay::AskCloudText);
            break;
        case SetupStep::SETUP_CLOUD:
            drawWebsocketCloud();
            break;
        case SetupStep::ASK_CALIBRATE_OTHER_BUTTONS:
            drawLargeText(setupdisplay::AskSetupOtherButtonsText);
            break;
        case SetupStep::FINAL_INFORMATION:
            drawLargeText(setupdisplay::FinalInformationText);
            break;
        }
    }

    if (m_current_setupStep == SetupStep::INFORMATION)
    {
        if (espchrono::ago(m_menu_opened_timestamp) > 5s)
        {
            nextStep();
        }

        m_init_text_progressbar.redraw(espchrono::ago(m_menu_opened_timestamp) / 50ms);
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
    switch (m_current_setupStep)
    {
    case SetupStep::INFORMATION:
        if (espchrono::ago(m_menu_opened_timestamp) > 500ms)
        {
            nextStep();
        }
        return;
    case SetupStep::ASK_SETUP_CLOUDS:
    {
        switch (button)
        {
        case espgui::Left: // skip cloud setup
            m_current_setupStep = SetupStep::ASK_CALIBRATE_OTHER_BUTTONS;
            break;
        case espgui::Right: // enter cloud setup
            m_current_setupStep = SetupStep::SETUP_CLOUD;
            configs.write_config(configs.feature.cloud.isEnabled, true);
            configs.write_config(configs.feature.udpcloud.isEnabled, true);
            reload_tasks();
            break;
        default:;
        }
        return;
    }
    case SetupStep::SETUP_CLOUD:
    {
        switch (button)
        {
        case espgui::Up:
            if (m_cloud_selected_item > 0)
            {
                m_cloud_selected_item = static_cast<setupdisplay::CurrentCloudSelect>(m_cloud_selected_item-1);
            }
            else
                m_cloud_selected_item = static_cast<setupdisplay::CurrentCloudSelect>(setupdisplay::CurrentCloudSelect::_LAST-1);
            break;
        case espgui::Down:
            if (m_cloud_selected_item < setupdisplay::CurrentCloudSelect::_LAST-1)
            {
                m_cloud_selected_item = static_cast<setupdisplay::CurrentCloudSelect>(m_cloud_selected_item+1);
            }
            else
            {
                m_cloud_selected_item = static_cast<setupdisplay::CurrentCloudSelect>(0);
            }
            break;
        case espgui::Right:
            switch (m_cloud_selected_item)
            {
            case setupdisplay::CLOUD_ENABLE:
            {
                clearArea();
                configs.write_config(configs.cloudSettings.cloudEnabled, !configs.cloudSettings.cloudEnabled.value());
                break;
            }
            case setupdisplay::CLOUD_URL:
            {
                espgui::pushScreen<CloudURLChangeScreen>();
                break;
            }
            case setupdisplay::CLOUD_KEY:
            {
                espgui::pushScreen<CloudKeyChangeScreen>();
                break;
            }
            case setupdisplay::DONE:
            {
                nextStep();
                return;
            }
            default:;
            }
            break;
        default:;
        }
        drawWebsocketCloud();
        return;
    }
    case SetupStep::ASK_CALIBRATE_OTHER_BUTTONS:
    {
        switch (button)
        {
        case espgui::Left: // skip other button setup
            m_current_setupStep = SetupStep::FINAL_INFORMATION;
            break;
        case espgui::Right: // enter other button setup (pushScreen)
            m_current_setupStep = SetupStep::FINAL_INFORMATION;
            espgui::pushScreen<ExtraButtonCalibrateMenu>();
            break;
        default:;
        }
        return;
    }
    case SetupStep::FINAL_INFORMATION:
    {
        configs.write_config(configs.boardcomputerHardware.setupFinished, true);
        if (espgui::displayStack.empty())
        {
            switchScreen<StatusDisplay>();
        }
        else
        {
            espgui::popScreen();
        }
    }
    default:;
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
            m_button_cal_finished = true;
        }
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
    if (auto result = configs.write_config(configs.dpadMappingLeft, m_leftButton); !result)
    {
        BobbyErrorHandler{}.errorOccurred(std::move(result).error());
        return;
    }
    else
    {
        ESP_LOGI(setupdisplay::TAG, "Left button set to %d", m_leftButton);
    }

    if (auto result = configs.write_config(configs.dpadMappingRight, m_rightButton); !result)
    {
        BobbyErrorHandler{}.errorOccurred(std::move(result).error());
        return;
    }
    else
    {
        ESP_LOGI(setupdisplay::TAG, "Right button set to %d", m_rightButton);
    }
    if (auto result = configs.write_config(configs.dpadMappingUp, m_upButton); !result)
    {
        BobbyErrorHandler{}.errorOccurred(std::move(result).error());
        return;
    }
    else
    {
        ESP_LOGI(setupdisplay::TAG, "Up button set to %d", m_upButton);
    }
    if (auto result = configs.write_config(configs.dpadMappingDown, m_downButton); !result)
    {
        BobbyErrorHandler{}.errorOccurred(std::move(result).error());
        return;
    }
    else
    {
        ESP_LOGI(setupdisplay::TAG, "Down button set to %d", m_downButton);
    }
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
    // ToDo: If menu entered because out of calibration, check if nextStep is also out of calibration. If not, exit into StatusDisplay via switchScreen

    switch(m_current_setupStep)
    {
    case SetupStep::INFORMATION:
        m_current_setupStep = SetupStep::BASIC_BUTTONS;
        break;
    case SetupStep::BASIC_BUTTONS:
        // m_current_setupStep = SetupStep::CALIBRATE_POTIS; ToDo: Implement with real hardware
        m_current_setupStep = SetupStep::ASK_SETUP_CLOUDS;
        break;
    case SetupStep::CALIBRATE_POTIS:
        m_current_setupStep = SetupStep::ASK_SETUP_CLOUDS;
        break;
    case SetupStep::ASK_SETUP_CLOUDS:
        m_current_setupStep = SetupStep::SETUP_CLOUD;
        break;
    case SetupStep::SETUP_CLOUD:
        m_current_setupStep = SetupStep::ASK_CALIBRATE_OTHER_BUTTONS;
        break;
    case SetupStep::ASK_CALIBRATE_OTHER_BUTTONS:
        m_current_setupStep = SetupStep::FINAL_INFORMATION;
        break;
    case SetupStep::FINAL_INFORMATION:
        break;
    }
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

    if (m_button_cal_finished)
    {
        return;
    }

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

void SetupDisplay::drawWebsocketCloud() const
{
    const auto spacing = 2;
    const auto x = 20;
    int y = 50;
    int width;

    tft.setTextColor(m_cloud_selected_item == setupdisplay::CLOUD_ENABLE ? TFT_YELLOW : TFT_WHITE);
    width = tft.drawString(fmt::format("* Cloud Enable ({})", configs.cloudSettings.cloudEnabled.value() ? "Enabled":"Disabled"), x, y);
    tft.drawLine(x, y+tft.fontHeight(), x+width, y+tft.fontHeight(), m_cloud_selected_item == setupdisplay::CLOUD_ENABLE ? TFT_YELLOW : TFT_BLACK);
    y += tft.fontHeight() + spacing;

    tft.setTextColor(m_cloud_selected_item == setupdisplay::CLOUD_URL ? TFT_YELLOW : TFT_WHITE);
    width = tft.drawString(fmt::format("* Cloud URL ({})", configs.cloudUrl.value()), x, y);
    tft.drawLine(x, y+tft.fontHeight(), x+width, y+tft.fontHeight(), m_cloud_selected_item == setupdisplay::CLOUD_URL ? TFT_YELLOW : TFT_BLACK);
    y += tft.fontHeight() + spacing;

    tft.setTextColor(m_cloud_selected_item == setupdisplay::CLOUD_KEY ? TFT_YELLOW : TFT_WHITE);
    width = tft.drawString(fmt::format("* Cloud Key ({})", configs.cloudSettings.cloudKey.value()), x, y);
    tft.drawLine(x, y+tft.fontHeight(), x+width, y+tft.fontHeight(), m_cloud_selected_item == setupdisplay::CLOUD_KEY ? TFT_YELLOW : TFT_BLACK);
    y += tft.fontHeight() + spacing;

    tft.setTextColor(m_cloud_selected_item == setupdisplay::DONE ? TFT_YELLOW : TFT_WHITE);
    width = tft.drawString("* Done", x, y);
    tft.drawLine(x, y+tft.fontHeight(), x+width, y+tft.fontHeight(), m_cloud_selected_item == setupdisplay::DONE ? TFT_YELLOW : TFT_BLACK);
    y += tft.fontHeight() + spacing;
}
