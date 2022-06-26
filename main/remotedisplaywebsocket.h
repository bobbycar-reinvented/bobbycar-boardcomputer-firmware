#pragma once

#include <cstdint>
#include <string>
#include <string_view>

// 3rdparty lib includes
#include <fmt/core.h>

// local includes
#include "cloud.h"

#include "esp_log.h"

#define RDWS_TAG "remotedisplay"

namespace remotedisplay
{

namespace
{

enum class msg_type : uint8_t
{
    drawCentreString,
    drawChar,
    drawCircle,
    drawEllipse,
    drawHLine,
    drawVLine,
    drawLine,
    drawPixel,
    drawRect,
    drawRightString,
    drawRoundRect,
    drawString,
    drawSunkenRect,
    drawTriangle,
    fillCircle,
    fillEllipse,
    fillRect,
    fillRoundRect,
    fillScreen,
    fillTriangle
};

struct drawString_msg
{
    int16_t x, y;
    uint8_t font;
};
static_assert(sizeof(drawString_msg) == 6, "wrong size");

struct drawChar_msg
{
    int16_t x, y;
    uint16_t c, color, bg;
    uint8_t size;
};
static_assert(sizeof(drawChar_msg) == 12, "wrong size");

struct drawCircle_msg
{
    int16_t x, y, r;
    uint16_t color;
};
static_assert(sizeof(drawCircle_msg) == 8, "wrong size");

struct drawEllipse_msg
{
    int16_t x, y, rx, ry;
    uint16_t color;
};
static_assert(sizeof(drawEllipse_msg) == 10, "wrong size");

struct drawHVLine_msg
{
    int16_t x, y, wh;
    uint16_t color;
};
static_assert(sizeof(drawHVLine_msg) == 8, "wrong size");

struct drawLine_msg
{
    int16_t xs, ys, xe, ye;
    uint16_t color;
};
static_assert(sizeof(drawLine_msg) == 10, "wrong size");

struct drawPixel_msg
{
    int16_t x, y;
    uint16_t color;
};
static_assert(sizeof(drawPixel_msg) == 6, "wrong size");

struct drawRect_msg
{
    int16_t x, y, w, h;
    uint16_t color;
};
static_assert(sizeof(drawRect_msg) == 10, "wrong size");

struct drawRoundRect_msg
{
    int16_t x, y, w, h, radius;
    uint16_t color;
};
static_assert(sizeof(drawRoundRect_msg) == 12, "wrong size");

struct drawSunkenRect_msg
{
    int16_t x, y, w, h;
    uint16_t color0, color1, color2;
};
static_assert(sizeof(drawSunkenRect_msg) == 14, "wrong size");

struct drawTriangle_msg
{
    int16_t x1, y1, x2, y2, x3, y3;
    uint16_t color;
};
static_assert(sizeof(drawTriangle_msg) == 14, "wrong size");

constexpr size_t HEADER_SIZE = 1;
void emitMessageHeader(std::string &dst, msg_type msg_type)
{
    dst += (char)msg_type;
}

void sendDrawMsg(msg_type type, std::string_view msg)
{
    std::string buf;
    emitMessageHeader(buf, type);
    buf += msg;

    cloudSendDisplay(buf);
}

void drawGenericString(msg_type type, std::string_view string, int32_t x, int32_t y, uint8_t font)
{
    if (string.size() > UINT8_MAX)
    {
        ESP_LOGW(RDWS_TAG, "String size too long (%zu > UINT8_MAX)", string.size());
        return;
    }

    drawString_msg dcstr = { (int16_t)x, (int16_t)y, font };
    std::string buf;
    emitMessageHeader(buf, msg_type::drawCentreString);
    buf += std::string_view((char *)&dcstr, sizeof(dcstr));
    buf += (char)string.length();
    buf += string;

    cloudSendDisplay(buf);
}

} // namespace

void drawCentreString(std::string_view string, int32_t x, int32_t y, uint8_t font)
{
    drawGenericString(msg_type::drawCentreString, string, x, y, font);
}

void drawChar(int32_t x, int32_t y, uint16_t c, uint16_t color, uint16_t bg, uint8_t size)
{
    drawChar_msg dc = { (int16_t)x, (int16_t)y, (uint16_t)c, color, bg, size };
    sendDrawMsg(msg_type::drawChar, std::string_view((char *)&dc, sizeof(dc)));
}

void drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color)
{
    drawCircle_msg dcirc = { (int16_t)x, (int16_t)y, (int16_t)r, (uint16_t)color };
    sendDrawMsg(msg_type::drawCircle, std::string_view((char *)&dcirc, sizeof(dcirc)));
}

void drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color)
{
    drawEllipse_msg dellip = { (int16_t)x, (int16_t)y, (int16_t)rx, (int16_t)ry, color };
    sendDrawMsg(msg_type::drawEllipse, std::string_view((char *)&dellip, sizeof(dellip)));
}

void drawFastHLine(int32_t x, int32_t y, int32_t w, uint16_t color)
{
    drawHVLine_msg dhl = { (int16_t)x, (int16_t)y, (int16_t)w, color };
    sendDrawMsg(msg_type::drawHLine, std::string_view((char *)&dhl, sizeof(dhl)));
}

void drawFastVLine(int32_t x, int32_t y, int32_t h, uint16_t color)
{
    drawHVLine_msg dvl = { (int16_t)x, (int16_t)y, (int16_t)h, color };
    sendDrawMsg(msg_type::drawVLine, std::string_view((char *)&dvl, sizeof(dvl)));
}

void drawLine(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint16_t color)
{
    drawLine_msg dl = { (int16_t)xs, (int16_t)ys, (int16_t)xe, (int16_t)ye, color };
    sendDrawMsg(msg_type::drawLine, std::string_view((char *)&dl, sizeof(dl)));
}

void drawPixel(int32_t x, int32_t y, uint16_t color)
{
    return; // wont support
    drawPixel_msg dp = { (int16_t)x, (int16_t)y, color };
    sendDrawMsg(msg_type::drawPixel, std::string_view((char *)&dp, sizeof(dp)));
}

void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
{
    // same parameters as fillRect -> can use same struct
    drawRect_msg dr = { (int16_t)x, (int16_t)y, (int16_t)w, (int16_t)h, (uint16_t)color };
    sendDrawMsg(msg_type::drawRect, std::string_view((char *)&dr, sizeof(dr)));
}

void drawRightString(std::string_view string, int32_t x, int32_t y, uint8_t font)
{
    drawGenericString(msg_type::drawRightString, string, x, y, font);
}

void drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color)
{
    drawRoundRect_msg drr = {
        (int16_t)x, (int16_t)y, (int16_t)w, (int16_t)h,
        (int16_t)radius, (uint16_t)color
    };
    sendDrawMsg(msg_type::drawRoundRect, std::string_view((char *)&drr, sizeof(drr)));
}

void drawString(std::string_view string, int32_t poX, int32_t poY, uint8_t font)
{
    drawGenericString(msg_type::drawString, string, poX, poY, font);
}

void drawSunkenRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color0, uint32_t color1, uint32_t color2)
{
    drawSunkenRect_msg dsr = {
        (int16_t)x, (int16_t)y, (int16_t)w, (int16_t)h,
        (uint16_t)color0, (uint16_t)color1, (uint16_t)color2
    };
    sendDrawMsg(msg_type::drawSunkenRect, std::string_view((char *)&dsr, sizeof(dsr)));
}

void drawTriangle(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color)
{
    drawTriangle_msg dt = {
        (int16_t)x1, (int16_t)y1, (int16_t)x2, (int16_t)y2, (int16_t)x3, (int16_t)y3,
        (uint16_t)color
    };
    sendDrawMsg(msg_type::drawTriangle, std::string_view((char *)&dt, sizeof(dt)));
}


void fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color)
{
    drawCircle_msg fcirc = { (int16_t)x, (int16_t)y, (int16_t)r, (uint16_t) color };
    sendDrawMsg(msg_type::fillCircle, std::string_view((char *)&fcirc, sizeof(fcirc)));
}

void fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color)
{
    drawEllipse_msg fellip = { (int16_t)x, (int16_t)y, (int16_t)rx, (int16_t)ry, (uint16_t) color };
    sendDrawMsg(msg_type::fillEllipse, std::string_view((char *)&fellip, sizeof(fellip)));
}

void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t color)
{
    drawRect_msg fr = { (int16_t)x, (int16_t)y, (int16_t)w, (int16_t)h, color };
    sendDrawMsg(msg_type::fillRect, std::string_view((char *)&fr, sizeof(fr)));
}

void fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color)
{
    drawRoundRect_msg frr = {
        (int16_t)x, (int16_t)y, (int16_t)w, (int16_t)h,
        (int16_t)radius, (uint16_t)color
    };
    sendDrawMsg(msg_type::fillRoundRect, std::string_view((char *)&frr, sizeof(frr)));
}

void fillScreen(uint32_t color)
{
    uint16_t fs = (uint16_t)color;
    sendDrawMsg(msg_type::fillScreen, std::string_view((char *)&fs, sizeof(fs)));
}

void fillTriangle(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color)
{
    drawTriangle_msg ft = {
        (int16_t)x1, (int16_t)y1, (int16_t)x2, (int16_t)y2, (int16_t)x3, (int16_t)y3,
        (uint16_t)color
    };
    sendDrawMsg(msg_type::fillTriangle, std::string_view((char *)&ft, sizeof(ft)));
}

} // namespace remotedisplay
