#pragma once

// system includes
#include <cstdint>
#include <string>
#include <fmt/core.h>

void cloudSendDisplay(std::string_view data);

void handleDrawPixel(uint16_t x, uint16_t y, uint16_t color);
void handleDrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void handleFillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void handleDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void handleFillScreen(uint16_t color);

void handleDrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    cloudSendDisplay(fmt::format("{{\"type\":\"drawPixel\",\"x\":{},\"y\":{},\"C\":\"{}\"}}", x, y, color));
}

void handleDrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    cloudSendDisplay(fmt::format("{{\"type\":\"drawRect\",\"x\":{},\"y\":{},\"w\":{},\"h\":{},\"C\":\"{}\"}}", x, y, width, height, color));
}

void handleFillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    cloudSendDisplay(fmt::format("{{\"type\":\"fillRect\",\"x\":{},\"y\":{},\"w\":{},\"h\":{},\"C\":\"{}\"}}", x, y, width, height, color));
}

void handleDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    cloudSendDisplay(fmt::format("{{\"type\":\"drawLine\",\"x1\":{},\"y1\":{},\"x2\":{},\"y2\":{},\"C\":\"{}\"}}", x1, y1, x2, y2, color));
}

void handleFillScreen(uint16_t color)
{
    cloudSendDisplay(fmt::format("{{\"type\":\"fillScreen\",\"C\":\"{}\"}}", color));
}
