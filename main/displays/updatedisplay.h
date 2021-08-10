#pragma once

// system includes
#include <array>
#include <string>

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#ifdef FEATURE_OTA
#include <espasyncota.h>
#endif
#include <fmt/core.h>

// local includes
#include "display.h"
#include "actions/switchscreenaction.h"
#include "globals.h"
#include "texts.h"
#include "widgets/label.h"
#include "widgets/progressbar.h"
#include "ota.h"

namespace {
class MainMenu;
}

namespace {
#ifdef FEATURE_OTA
class UpdateDisplay : public Display, public BackActionInterface<SwitchScreenAction<MainMenu>>
{
public:
    void start() override;
    void initScreen() override;
    void redraw() override;
    void confirm() override;

private:
    Label m_statusLabel{120, 75};
    Label m_progressLabel{120, 100};
    Label m_totalLabel{120, 125};

    ProgressBar m_progressBar{20, 200, 200, 10, 0, 100};
};

void UpdateDisplay::start()
{
}

void UpdateDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(TEXT_UPDATE, 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.drawString("Status:", 20, m_statusLabel.y());
    m_statusLabel.start();

    tft.drawString("Progress:", 20, m_progressLabel.y());
    m_progressLabel.start();

    tft.drawString("Total:", 20, m_totalLabel.y());
    m_totalLabel.start();

    m_progressBar.start();
}

void UpdateDisplay::redraw()
{
    if (asyncOta)
    {
        m_statusLabel.redraw(toString(asyncOta->status()));
        const auto progress = asyncOta->progress();
        m_progressLabel.redraw(std::to_string(progress));
        if (const auto totalSize = asyncOta->totalSize())
        {
            m_totalLabel.redraw(std::to_string(*totalSize));
            m_progressBar.redraw(float(progress) / *totalSize * 100);
        }
        else
        {
            m_totalLabel.clear();
            m_progressBar.redraw(0);
        }
    }
    else
    {
        m_statusLabel.clear();
        m_progressLabel.clear();
        m_totalLabel.clear();

        m_progressBar.redraw(0);
    }
}

void UpdateDisplay::confirm()
{
    //if (m_finished)
    //    switchScreen<StatusDisplay>();

    if (const auto result = triggerOta(stringSettings.otaUrl); !result)
        ESP_LOGE("BOBBY", "triggerOta() failed with %.*s", result.error().size(), result.error().data());
}
#endif
}
