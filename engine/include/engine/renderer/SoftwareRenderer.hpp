#pragma once

#include <engine/renderer/ScreenPoint.hpp>

#include <vector>
#include <cstdint>

class SoftwareRenderer
{
private:
    int width;
    int height;
    std::vector<std::uint32_t> framebuffer;

public:
    SoftwareRenderer(int width, int height, std::uint32_t initialColor);
    void drawPixel(const ScreenPoint &point, std::uint32_t color);
    void drawLine(const ScreenPoint &pointStart, const ScreenPoint &pointEnd, std::uint32_t color);
    void drawTriangleOutline(const ScreenPoint &a, const ScreenPoint &b, const ScreenPoint &c, std::uint32_t color);
    std::uint32_t *data();
};