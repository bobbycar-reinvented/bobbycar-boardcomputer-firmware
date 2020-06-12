#pragma once

#include "globals.h"

namespace {
class VerticalMeter
{
public:
    VerticalMeter(const char *text, int x, int y);

    void start();
    void redraw(int value);

private:
    const char * const m_text;
    const int m_x;
    const int m_y;

    int m_oldValue{};
};

VerticalMeter::VerticalMeter(const char *text, int x, int y) :
    m_text{text}, m_x{x}, m_y{y}
{
}

void VerticalMeter::start()
{
    int w = 36;
    tft.drawRect(m_x, m_y, w, 155, TFT_GREY);
    tft.fillRect(m_x + 2, m_y + 19, w - 3, 155 - 38, TFT_WHITE);
    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.drawCentreString(m_text, m_x + w / 2, m_y + 2, 2);

    for (int i = 0; i < 110; i += 10)
        tft.drawFastHLine(m_x + 20, m_y + 27 + i, 6, TFT_BLACK);

    for (int i = 0; i < 110; i += 50)
        tft.drawFastHLine(m_x + 20, m_y + 27 + i, 9, TFT_BLACK);

    tft.fillTriangle(m_x + 3, m_y + 127, m_x + 3 + 16, m_y + 127, m_x + 3, m_y + 127 - 5, TFT_RED);
    tft.fillTriangle(m_x + 3, m_y + 127, m_x + 3 + 16, m_y + 127, m_x + 3, m_y + 127 + 5, TFT_RED);

    tft.drawCentreString("---", m_x + w / 2, m_y + 155 - 18, 2);
}

void VerticalMeter::redraw(int value)
{
    char buf[8];
    dtostrf(value, 4, 0, buf);
    tft.drawRightString(buf, m_x + 36 - 5, 187 - 27 + 155 - 18, 2);

    const int dx = 3 + m_x;
    if (value < 0.f) value = 0; // Limit value to emulate needle end stops
    if (value > 100.f) value = 100;

    while (value != m_oldValue) {
        const int dy = 187 + 100 - m_oldValue;
        if (m_oldValue > value)
        {
            tft.drawLine(dx, dy - 5, dx + 16, dy, TFT_WHITE);
            m_oldValue--;
            tft.drawLine(dx, dy + 6, dx + 16, dy + 1, TFT_RED);
        }
        else
        {
            tft.drawLine(dx, dy + 5, dx + 16, dy, TFT_WHITE);
            m_oldValue++;
            tft.drawLine(dx, dy - 6, dx + 16, dy - 1, TFT_RED);
        }
    }
}


}
