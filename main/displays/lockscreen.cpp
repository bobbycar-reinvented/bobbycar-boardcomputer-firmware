#include "lockscreen.h"

// 3rdparty lib includes
#include <tftinstance.h>
#include <screenmanager.h>

// local includes
#include "globals.h"
#include "utils.h"
#include "texts.h"
#include "buttons.h"
#include "displays/menus/mainmenu.h"

void Lockscreen::start()
{
    m_numbers = {0,0,0,0};
    m_currentIndex = 0;
    m_pressed = false;
    m_rotated = 0;

    m_oldMode = currentMode;
    currentMode = &m_mode;

    profileButtonDisabled = !settings.lockscreen.allowPresetSwitch;
}

void Lockscreen::initScreen()
{
    espgui::tft.fillScreen(TFT_BLACK);
    espgui::tft.setTextFont(4);
    espgui::tft.setTextColor(TFT_YELLOW);

    espgui::tft.drawString(TEXT_LOCKVEHICLE, 5, 5);

    espgui::tft.fillRect(0, 34, espgui::tft.width(), 3, TFT_WHITE);

    espgui::tft.setTextColor(TFT_WHITE);
    espgui::tft.drawString("Enter code to unlock:", 0, 50);

    espgui::tft.setTextColor(TFT_WHITE, TFT_BLACK);

    for(int i = 0; i <= 3; i++)
    {
        drawRect(i, 3, TFT_WHITE);
        drawRect(i, 4, TFT_WHITE);
    }

    for (auto &label : m_labels)
        label.start();

    espgui::tft.setTextFont(7);

    drawRect(0, 1, TFT_YELLOW);
    drawRect(0, 2, TFT_YELLOW);
    m_labels[0].redraw(std::to_string(m_numbers[0]));
}

void Lockscreen::update()
{
    // just in case someone changes that settings somehow
    profileButtonDisabled = !settings.lockscreen.allowPresetSwitch;
}

void Lockscreen::redraw()
{
    if (m_pressed)
    {
        drawRect(m_currentIndex, 1, TFT_BLACK);
        drawRect(m_currentIndex, 2, TFT_BLACK);

        if (++m_currentIndex>=4)
        {
            if (m_numbers == settings.lockscreen.pin)
            {
                espgui::switchScreen<MainMenu>();
#ifdef LOCKSCREEN_PLUGIN
#pragma message "Activating Lockscreen Plugin"
#include LOCKSCREEN_PLUGIN
#endif
                return;
            }

            m_numbers = {0,0,0,0};
            m_currentIndex = 0;
            std::for_each(std::begin(m_labels) + 1, std::end(m_labels), [](auto &label){ label.redraw({}); });
        }

        m_labels[m_currentIndex].redraw(std::to_string(m_numbers[m_currentIndex]));

        drawRect(m_currentIndex, 1, TFT_YELLOW);
        drawRect(m_currentIndex, 2, TFT_YELLOW);

        m_pressed = false;
    }

    if (m_rotated)
    {
        m_numbers[m_currentIndex] -= m_rotated;

        if (m_numbers[m_currentIndex] < 0)
            m_numbers[m_currentIndex]+=10;
        else if (m_numbers[m_currentIndex] > 9)
            m_numbers[m_currentIndex]-=10;

        m_labels[m_currentIndex].redraw(std::to_string(m_numbers[m_currentIndex]));

        m_rotated = 0;
    }
}

void Lockscreen::stop()
{
    Base::stop();

    if (currentMode == &m_mode)
    {
        // to avoid crash after deconstruction
        m_mode.stop();
        lastMode = nullptr;

        currentMode = m_oldMode;
    }

    profileButtonDisabled = false;
}

void Lockscreen::confirm()
{
    m_pressed = true;
}

void Lockscreen::back()
{
}

void Lockscreen::rotate(int offset)
{
    m_rotated += offset;
}

void Lockscreen::drawRect(int index, int offset, uint32_t color) const
{
    espgui::tft.drawRect(m_labels[index].x()-offset, m_labels[index].y()-offset, boxWidth+(offset*2), boxHeight+(offset*2), color);
}
