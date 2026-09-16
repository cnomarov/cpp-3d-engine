#include <engine/renderer/SoftwareRenderer.hpp>

#include <cmath>
#include <algorithm>

SoftwareRenderer::SoftwareRenderer(int width, int height, std::uint32_t initialColor) : width(width), height(height), framebuffer(width * height, initialColor)
{
}

void SoftwareRenderer::drawPixel(const ScreenPoint &point, std::uint32_t color)
{
    if (point.x < 0 || point.x >= width || point.y < 0 || point.y >= height)
    {
        return;
    }

    const int index = point.y * width + point.x;
    framebuffer[index] = color;
}

void SoftwareRenderer::drawLine(const ScreenPoint &pointStart, const ScreenPoint &pointEnd, std::uint32_t color)
{
    const int deltaX = pointEnd.x - pointStart.x;
    const int deltaY = pointEnd.y - pointStart.y;

    const int steps = std::max(std::abs(deltaX), std::abs(deltaY));
    if (steps == 0)
    {
        drawPixel(pointStart, color);
        return;
    }

    const double xIncrement = static_cast<double>(deltaX) / steps;
    const double yIncrement = static_cast<double>(deltaY) / steps;

    int currentStep = 0;
    double currentX = pointStart.x;
    double currentY = pointStart.y;

    while (currentStep <= steps)
    {
        drawPixel({static_cast<int>(std::round(currentX)), static_cast<int>(std::round(currentY))}, color);

        currentX += xIncrement;
        currentY += yIncrement;
        currentStep++;
    }
}

void SoftwareRenderer::drawTriangleOutline(const ScreenPoint &a, const ScreenPoint &b, const ScreenPoint &c, std::uint32_t color)
{
    drawLine(a, b, color);
    drawLine(b, c, color);
    drawLine(c, a, color);
}

std::uint32_t *SoftwareRenderer::data()
{
    return framebuffer.data();
}