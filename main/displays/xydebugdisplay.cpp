#include "xydebugdisplay.h"

// 3rdparty lib includes
#include <fmt/core.h>
#include <screenmanager.h>
#include <tftinstance.h>

// local includes
#include "bobbybuttons.h"

XYDebugDisplay::XYDebugDisplay() : m_labelCoordinates{5, 5} {}

void XYDebugDisplay::initScreen()
{
    Base::initScreen();
    m_labelCoordinates.start();
}

void XYDebugDisplay::redraw()
{
    using namespace espgui;

    Base::redraw();
    m_labelCoordinates.redraw(fmt::format("X: {}, Y: {}", m_current_cursor.x, m_current_cursor.y));

    if (m_current_cursor.x != m_last_cursor.x || m_current_cursor.y != m_last_cursor.y)
    {
        tft.fillCircle(m_last_cursor.x, m_last_cursor.y, 2, TFT_BLACK);
        tft.fillCircle(m_current_cursor.x, m_current_cursor.y, 2, TFT_WHITE);

        m_last_cursor = m_current_cursor;
    }
}

void XYDebugDisplay::buttonPressed(espgui::Button button)
{
    switch (button)
    {
    using espgui::Button;
    case Button::Left:
    case Button::Right:
    case Button::Up:
    case Button::Down:
        espgui::popScreen();
        break;
    default:;
    }

    switch (BobbyButton(button))
    {
    case BobbyButton::Left2:
        if (m_current_cursor.x > 0)
        {
            --m_current_cursor.x;
        }
        break;
    case BobbyButton::Right2:
        if (m_current_cursor.x < espgui::tft.width() - 1)
        {
            ++m_current_cursor.x;
        }
        break;
    case BobbyButton::Up2:
        if (m_current_cursor.y > 0)
        {
            --m_current_cursor.y;
        }
        break;
    case BobbyButton::Down2:
        if (m_current_cursor.y < espgui::tft.height() - 1)
        {
            ++m_current_cursor.y;
        }
        break;
    default:;
    }
}
