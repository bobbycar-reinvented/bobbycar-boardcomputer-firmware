#include "updatedisplay.h"

// system includes
#include <array>
#include <string>

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <esp_ota_ops.h>
#include <espasyncota.h>
#include <fontrenderer.h>
#include <screenmanager.h>
#include <tftcolors.h>
#include <tftinterface.h>

// local includes
#include "globals.h"
#include "newsettings.h"
#include "ota.h"

namespace bobby {

void UpdateDisplay::initScreen(espgui::TftInterface &tft)
{
    Base::initScreen(tft);

    auto font = espgui::FontRenderer{tft};

    font.drawString("Status:", 20, m_statusLabel.y(), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
    m_statusLabel.start(tft);

    font.drawString("Progress:", 20, m_progressLabel.y(), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
    m_progressLabel.start(tft);

    font.drawString("Total:", 20, m_totalLabel.y(), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
    m_totalLabel.start(tft);

    m_messageLabel.start(tft);

    m_progressBar.start(tft);

    if (const esp_app_desc_t *app_desc = esp_ota_get_app_description())
    {
        font.drawString(app_desc->version, 20, 250, TFT_ORANGE, TFT_BLACK, 4);
    }

    m_newVersionLabel.start(tft);
}

void UpdateDisplay::redraw(espgui::TftInterface &tft)
{
    Base::redraw(tft);

    if (ota::isOtaInProgress())
    {
        m_statusLabel.redraw(tft, toString(ota::otaStatus()), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
        const auto progress = ota::otaProgress();
        m_progressLabel.redraw(tft, std::to_string(progress), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
        if (const auto totalSize = ota::otaTotalSize(); totalSize && *totalSize > 0)
        {
            m_totalLabel.redraw(tft, std::to_string(*totalSize), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
            m_progressBar.redraw(tft, ota::otaPercent());
        }
        else
        {
            m_totalLabel.clear(tft, TFT_BLACK);
            m_progressBar.redraw(tft, 0);
        }
        m_messageLabel.redraw(tft, ota::otaMessage(), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);

        if (const auto appDesc = ota::otaAppDesc(); appDesc)
        {
            m_newVersionLabel.redraw(tft, appDesc->version, espgui::TFT_GREEN, espgui::TFT_BLACK, 4);
        }
        else
            m_newVersionLabel.clear(tft, espgui::TFT_BLACK);
    }
    else
    {
        m_statusLabel.clear(tft, espgui::TFT_BLACK);
        m_progressLabel.clear(tft, espgui::TFT_BLACK);
        m_totalLabel.clear(tft, espgui::TFT_BLACK);
        m_messageLabel.clear(tft, espgui::TFT_BLACK);

        m_progressBar.redraw(tft, 0);

        m_newVersionLabel.clear(tft, espgui::TFT_BLACK);
    }
}

void UpdateDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);

    switch (button)
    {
    using espgui::Button;
    case Button::Left:
        espgui::popScreen();
        break;
    case Button::Right:
        if (const auto result = ota::triggerOta(configs.otaUrl.value()); !result)
            ESP_LOGE("BOBBY", "triggerOta() failed with %.*s", result.error().size(), result.error().data());
        break;
    default:;
    }
}

std::string UpdateDisplay::title() const
{
    return "Update";
}
} // namespace bobby
