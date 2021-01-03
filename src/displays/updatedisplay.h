#pragma once

#include <array>

#include <ArduinoOTA.h>
#include <WString.h>

#include "display.h"
#include "actions/switchscreenaction.h"
#include "globals.h"
#include "texts.h"
#include "widgets/label.h"
#include "widgets/progressbar.h"
#include "modes/ignoreinputmode.h"

namespace {
class StatusDisplay;
}

namespace {
#ifdef FEATURE_ARDUINOOTA
class UpdateDisplay : public Display, public DummyBack
{
public:
    UpdateDisplay(const String &title);
    UpdateDisplay(String &&title);

    void start() override;
    void initScreen() override;
    void redraw() override;
    void confirm() override;

public:
    bool m_finished;
    unsigned int m_progress;
    unsigned int m_total;
    ota_error_t m_error;
    bool m_errorValid;

private:
    const String m_title;

    Label m_progressLabel{20, 150};

    ProgressBar m_progressBar{20, 200, 200, 10, 0, 100};
};

UpdateDisplay::UpdateDisplay(const String &title) :
    m_title{title}
{}

UpdateDisplay::UpdateDisplay(String &&title) :
    m_title{std::move(title)}
{}

void UpdateDisplay::start()
{
    m_finished = false;
    m_progress = 0;
    m_total = 1;
    m_errorValid = false;
}

void UpdateDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(m_title, 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.drawString("Progress:", 20, 125);
    m_progressLabel.start();

    m_progressBar.start();
}

void UpdateDisplay::redraw()
{
    m_progressLabel.redraw(String{} + m_progress + '/' + m_total);

    m_progressBar.redraw(float(m_progress) / m_total * 100.f);
}

void UpdateDisplay::confirm()
{
    if (m_finished)
        switchScreen<StatusDisplay>();
}
#endif
}
