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

namespace remotedisplay {

enum class msg_type : uint8_t
{
    drawCentreString,
    drawChar,
    drawCircle,
    drawEllipse,
    drawLine,
    drawRect,
    fillRect,
    fillRoundRect,
    fillScreen
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

struct drawLine_msg
{
    int16_t xs, ys, xe, ye;
    uint16_t color;
};
static_assert(sizeof(drawLine_msg) == 10, "wrong size");

constexpr size_t HEADER_SIZE = 3;
void emitMessageHeader(std::string &dst, msg_type msg_type, uint8_t msg_size)
{
    dst += (char)msg_type;
    dst += (char)msg_size;
}

void drawCentreString(std::string_view string, int32_t x, int32_t y, uint8_t font)
{
    const size_t msg_size = HEADER_SIZE + sizeof(drawString_msg) + string.size();
    if (msg_size > UINT8_MAX)
    {
        ESP_LOGW(RDWS_TAG, "Msg size too long (%zu > UINT8_MAX)", msg_size);
        return;
    }

    drawString_msg dcstr = { (int16_t)x, (int16_t)y, font };
    std::string buf;
    emitMessageHeader(buf, msg_type::drawCentreString, msg_size);
    buf += std::string_view((char *)&dcstr, sizeof(dcstr));
    buf += string;

    cloudSendDisplay(buf);
}

void drawChar(int32_t x, int32_t y, uint16_t c, uint16_t color, uint16_t bg, uint8_t size)
{
    drawChar_msg dc = { (int16_t)x, (int16_t)y, (uint16_t)c, color, bg, size };
    std::string buf;
    emitMessageHeader(buf, msg_type::drawChar, HEADER_SIZE + sizeof(dc));
    buf += std::string_view((char *)&dc, sizeof(dc));

    cloudSendDisplay(buf);
}

void drawCircle(int32_t x, int32_t y, int32_t r, uint32_t color)
{
    drawCircle_msg dcirc = { (int16_t)x, (int16_t)y, (int16_t)r, (uint16_t)color };
    std::string buf;
    emitMessageHeader(buf, msg_type::drawCircle, HEADER_SIZE + sizeof(dcirc));
    buf += std::string_view((char *)&dcirc, sizeof(dcirc));

    cloudSendDisplay(buf);
}

void drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, uint16_t color)
{
    drawEllipse_msg dellip = { (int16_t)x, (int16_t)y, (int16_t)rx, (int16_t)ry, color };
    std::string buf;
    emitMessageHeader(buf, msg_type::drawEllipse, HEADER_SIZE + sizeof(dellip));
    buf += std::string_view((char *)&dellip, sizeof(dellip));

    cloudSendDisplay(buf);
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
    drawLine_msg dl = { (int16_t)xs, (int16_t)ye, (int16_t)xe, (int16_t)ye, color };
    std::string buf;
    emitMessageHeader(buf, msg_type::drawLine, HEADER_SIZE + sizeof(dl));
    buf += std::string_view((char *)&dl, sizeof(dl));

    cloudSendDisplay(buf);
}

void drawPixel(int32_t x, int32_t y, uint16_t color)
{
    return; // wont support
    cloudSendDisplay(fmt::format("_dp {} {} {}", x, y, color));
}

void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
{
    // same parameters as fillRect -> can use same struct
    drawRect_msg dr = { (int16_t)x, (int16_t)y, (int16_t)w, (int16_t)h, (uint16_t)color };
    std::string buf;
    emitMessageHeader(buf, msg_type::drawRect, HEADER_SIZE + sizeof(dr));
    buf += std::string_view((char *)&dr, sizeof(dr));

    cloudSendDisplay(buf);
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
    drawRect_msg fr = { (int16_t)x, (int16_t)y, (int16_t)w, (int16_t)h, color };
    std::string buf;
    emitMessageHeader(buf, msg_type::fillRect, HEADER_SIZE + sizeof(fr));
    buf += std::string_view((char *)&fr, sizeof(fr));

    cloudSendDisplay(buf);
}

void fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, uint32_t color)
{
    drawRoundRect_msg frr = {
        (int16_t)x, (int16_t)y, (int16_t)w, (int16_t)h,
        (int16_t)radius, (uint16_t)color
    };
    std::string buf;
    emitMessageHeader(buf, msg_type::fillRoundRect, HEADER_SIZE + sizeof(frr));
    buf += std::string_view((char *)&frr, sizeof(frr));

    cloudSendDisplay(buf);
}

void fillScreen(uint32_t color)
{
    uint16_t fs = (uint16_t)color;
    std::string buf;
    emitMessageHeader(buf, msg_type::fillScreen, HEADER_SIZE + sizeof(fs));
    buf += std::string_view((char *)&fs, sizeof(fs));

    cloudSendDisplay(buf);
}

void fillTriangle(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color)
{
    cloudSendDisplay(fmt::format("_ft {} {} {} {} {} {} {}", x1, y1, x2, y2, x3, y3, color));
}

} // namespace remotedisplay
