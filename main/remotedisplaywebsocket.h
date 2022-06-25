#pragma once

// 3rdparty lib includes
#include <fmt/core.h>

// local includes
#include "cloud.h"

#include "esp_log.h"

namespace remotedisplay {
void drawCentreString(std::string_view string, int32_t x, int32_t y, uint8_t font)
{
    cloudSendDisplay(fmt::format("_dcstr {} {} {} {}", x, y, string, font));
}

void drawChar(int32_t x, int32_t y, uint16_t c, uint16_t color, uint16_t bg, uint8_t size)
{
    cloudSendDisplay(fmt::format("_dc {} {} {} {} {}", x, y, c, color, bg, size));
}

void drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color)
{
    cloudSendDisplay(fmt::format("_dcirc {} {} {} {}", x, y, r, color));
}

void drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color)
{
    cloudSendDisplay(fmt::format("_dellip {} {} {} {} {}", x, y, rx, ry, color));
}

void drawFastHLine(int32_t x, int32_t y, int32_t w, uint16_t color)
{
    cloudSendDisplay(fmt::format("_dhl {} {} {} {}", x, y, w, color));
}

void drawFastVLine(int32_t x, int32_t y, int32_t h, uint16_t color)
{
    cloudSendDisplay(fmt::format("_dvl {} {} {} {}", x, y, h, color));
}

void drawLine(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint16_t color)
{
    cloudSendDisplay(fmt::format("_dl {} {} {} {} {}", xs, ys, xe, ye, color));
}

void drawPixel(int32_t x, int32_t y, uint16_t color)
{
    return; // wont support
    cloudSendDisplay(fmt::format("_dp {} {} {}", x, y, color));
}

void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
{
    ESP_LOGI("remotedisplay", "drawRect");
    cloudSendDisplay(fmt::format("_dr {} {} {} {} {}", x, y, w, h, color));
}

void drawRightString(std::string_view string, int32_t x, int32_t y, uint8_t font)
{
    cloudSendDisplay(fmt::format("_drs {} {} {} {}", x, y, string, font));
}

void drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color)
{
    cloudSendDisplay(fmt::format("_drr {} {} {} {} {} {}", x, y, w, h, radius, color));
}

void drawString(std::string_view string, int32_t poX, int32_t poY, uint8_t font)
{
    cloudSendDisplay(fmt::format("_ds {} {} {} {}", poX, poY, string, font));
}

void drawSunkenRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color0, uint32_t color1, uint32_t color2)
{
    cloudSendDisplay(fmt::format("_dsr {} {} {} {} {} {} {}", x, y, w, h, color0, color1, color2));
}

void drawTriangle(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color)
{
    cloudSendDisplay(fmt::format("_dt {} {} {} {} {} {} {}", x1, y1, x2, y2, x3, y3, color));
}


void fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color)
{
    cloudSendDisplay(fmt::format("_fcirc {} {} {} {}", x, y, r, color));
}

void fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color)
{
    cloudSendDisplay(fmt::format("_fellip {} {} {} {} {}", x, y, rx, ry, color));
}

void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t color)
{
    cloudSendDisplay(fmt::format("_fr {} {} {} {} {}", x, y, w, h, color));
}

void fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color)
{
    cloudSendDisplay(fmt::format("_frr {} {} {} {} {} {}", x, y, w, h, radius, color));
}

void fillScreen(uint32_t color)
{
    cloudSendDisplay(fmt::format("_fs {}", color));
}

void fillTriangle(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color)
{
    cloudSendDisplay(fmt::format("_ft {} {} {} {} {} {} {}", x1, y1, x2, y2, x3, y3, color));
}

} // namespace remotedisplay
