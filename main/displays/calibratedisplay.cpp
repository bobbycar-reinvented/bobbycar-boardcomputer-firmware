#include "calibratedisplay.h"

// 3rdparty lib includes
#include <tftinstance.h>
#include <screenmanager.h>

// local includes
#include "displays/menus/mainmenu.h"
#include "displays/statusdisplay.h"
#include "displays/menus/boardcomputerhardwaresettingsmenu.h"

CalibrateDisplay::CalibrateDisplay(bool bootup) :
    m_bootup{bootup}
{
}

std::string CalibrateDisplay::text() const
{
    return TEXT_CALIBRATE;
}

void CalibrateDisplay::start()
{
    Base::start();

    m_oldMode = currentMode;
    currentMode = &m_mode;
    m_selectedButton = 0;
    m_status = Status::Begin;
    copyFromSettings();
    m_gas = std::nullopt;
    m_brems = std::nullopt;
}

void CalibrateDisplay::initScreen()
{
    Base::initScreen();

    espgui::tft.setTextFont(4);
    espgui::tft.setTextColor(TFT_WHITE, TFT_BLACK);

    espgui::tft.drawString("gas:", 25, 47);
    espgui::tft.drawString("brems:", 25, 147);

    for (auto &label : m_labels)
        label.start();

    for (auto &progressBar : m_progressBars)
        progressBar.start();

    m_renderedButton = -1;
}

void CalibrateDisplay::update()
{
    Base::update();

    if (raw_gas)
        m_gas = cpputils::mapValueClamped<float>(*raw_gas, m_gasMin, m_gasMax, 0., 1000.);
    else
        m_gas = std::nullopt;

    if (raw_brems)
        m_brems = cpputils::mapValueClamped<float>(*raw_brems, m_bremsMin, m_bremsMax, 0., 1000.);
    else
        m_brems = std::nullopt;
}

void CalibrateDisplay::redraw()
{
    Base::redraw();

    m_labels[0].redraw(m_gas ? fmt::format("{:.02f}", *m_gas) : "?");
    m_labels[1].redraw(raw_gas ? std::to_string(*raw_gas) : "?");
    if (m_status == Status::GasMin)
        espgui::tft.setTextColor(TFT_RED, TFT_BLACK);
    m_labels[2].redraw(std::to_string(m_gasMin));
    if (m_status == Status::GasMin)
        espgui::tft.setTextColor(TFT_WHITE, TFT_BLACK);
    if (m_status == Status::GasMax)
        espgui::tft.setTextColor(TFT_RED, TFT_BLACK);
    m_labels[3].redraw(std::to_string(m_gasMax));
    if (m_status == Status::GasMax)
        espgui::tft.setTextColor(TFT_WHITE, TFT_BLACK);

    m_progressBars[0].redraw(m_gas ? *m_gas : 0);

    m_labels[4].redraw(m_brems ? fmt::format("{:.02f}", *m_brems) : "?");
    m_labels[5].redraw(raw_brems ? std::to_string(*raw_brems) : "?");
    if (m_status == Status::BremsMin)
        espgui::tft.setTextColor(TFT_RED, TFT_BLACK);
    m_labels[6].redraw(std::to_string(m_bremsMin));
    if (m_status == Status::BremsMin)
        espgui::tft.setTextColor(TFT_WHITE, TFT_BLACK);
    if (m_status == Status::BremsMax)
        espgui::tft.setTextColor(TFT_RED, TFT_BLACK);
    m_labels[7].redraw(std::to_string(m_bremsMax));
    if (m_status == Status::BremsMax)
        espgui::tft.setTextColor(TFT_WHITE, TFT_BLACK);

    m_progressBars[1].redraw(m_brems ? *m_brems : 0);

    m_labels[8].redraw([&](){
        switch (m_status)
        {
        case Status::Begin: return "Start calibrating?";
        case Status::GasMin: return "Release gas";
        case Status::GasMax: return "Press gas";
        case Status::BremsMin: return "Release brems";
        case Status::BremsMax: return "Press brems";
        case Status::Confirm: return "Verify";
        }
        __builtin_unreachable();
    }());

    {
        const auto failed = !m_gas || !m_brems || (m_status == Status::Confirm && (*m_gas > 100 || *m_brems > 100));
        const auto color = failed ? TFT_DARKGREY : TFT_WHITE;
        espgui::tft.setTextColor(color, TFT_BLACK);
        m_labels[9].redraw([&](){
            switch (m_status)
            {
            case Status::Begin: return "Yes";
            case Status::GasMin:
            case Status::GasMax:
            case Status::BremsMin:
            case Status::BremsMax: return "Next";
            case Status::Confirm: return "Save";
            }
            __builtin_unreachable();
        }());

        if (m_selectedButton != m_renderedButton && (m_selectedButton == 0 || m_renderedButton == 0))
            espgui::tft.drawRect(3, 275, 100, 27, m_selectedButton == 0 ? color : TFT_BLACK);
    }

    espgui::tft.setTextColor(TFT_WHITE, TFT_BLACK);
    m_labels[10].redraw([&](){
        switch (m_status)
        {
        case Status::Begin: return "No";
        case Status::GasMin:
        case Status::GasMax:
        case Status::BremsMin:
        case Status::BremsMax:
        case Status::Confirm: return "Abort";
        }
        __builtin_unreachable();
    }());

    if (m_selectedButton != m_renderedButton && (m_selectedButton == 1 || m_renderedButton == 1))
        espgui::tft.drawRect(123, 275, 100, 27, m_selectedButton == 1 ? TFT_WHITE : TFT_BLACK);

    m_renderedButton = m_selectedButton;
}

void CalibrateDisplay::stop()
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

void CalibrateDisplay::rotate(int offset)
{
    Base::rotate(offset);

    m_selectedButton += offset;

    if (m_selectedButton < 0)
        m_selectedButton = 1;
    if (m_selectedButton > 1)
        m_selectedButton = 0;
}

void CalibrateDisplay::confirm()
{
    switch (m_selectedButton)
    {
    case 0: // left button pressed
        if (!raw_gas || !raw_brems || !m_gas || !m_brems)
            return;

        switch (m_status)
        {
        case Status::Begin:
            m_status = Status::GasMin;
            break;
        case Status::GasMin:
            m_gasMin = *raw_gas;
            m_status = Status::GasMax;
            break;
        case Status::GasMax:
            m_gasMax = *raw_gas;
            m_status = Status::BremsMin;
            {
                const auto dead = (m_gasMax - m_gasMin)/20;
                m_gasMin += dead;
                m_gasMax -= dead;
            }
            break;
        case Status::BremsMin:
            m_bremsMin = *raw_brems;
            m_status = Status::BremsMax;
            break;
        case Status::BremsMax:
            m_bremsMax = *raw_brems;
            m_status = Status::Confirm;
            {
                const auto dead = (m_bremsMax - m_bremsMin)/20;
                m_bremsMin += dead;
                m_bremsMax -= dead;
            }
            break;
        case Status::Confirm:
            if (*m_gas > 100 || *m_brems > 100)
                return;
            copyToSettings();
            saveSettings();
            if (m_bootup)
                espgui::switchScreen<StatusDisplay>();
            else
                espgui::switchScreen<BoardcomputerHardwareSettingsMenu>();
        }
        break;
    case 1: // right button pressed
        back();
    }
}

void CalibrateDisplay::back()
{
    switch (m_status)
    {
    case Status::Begin:
        if (m_bootup)
            espgui::switchScreen<StatusDisplay>();
        else if (settings.lockscreen.keepLockedAfterReboot && settings.lockscreen.locked)
        {
            espgui::switchScreen<MainMenu>();
            settings.lockscreen.locked = false;
            saveSettings();
        }
        else
            espgui::switchScreen<BoardcomputerHardwareSettingsMenu>();
        break;
    case Status::GasMin:
    case Status::GasMax:
    case Status::BremsMin:
    case Status::BremsMax:
    case Status::Confirm:
        m_selectedButton = 0;
        m_status = Status::Begin;
        copyFromSettings();
    }
}

void CalibrateDisplay::copyFromSettings()
{
    m_gasMin = settings.boardcomputerHardware.gasMin;
    m_gasMax = settings.boardcomputerHardware.gasMax;
    m_bremsMin = settings.boardcomputerHardware.bremsMin;
    m_bremsMax = settings.boardcomputerHardware.bremsMax;
}

void CalibrateDisplay::copyToSettings()
{
    settings.boardcomputerHardware.gasMin = m_gasMin;
    settings.boardcomputerHardware.gasMax = m_gasMax;
    settings.boardcomputerHardware.bremsMin = m_bremsMin;
    settings.boardcomputerHardware.bremsMax = m_bremsMax;
}
