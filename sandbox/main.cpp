#include <iostream>

#include <engine/math/Vec2.hpp>
#include <memory>
#include <vector>
#include <fstream>
#include <SDL.h>
#include <cstdint>
#include <utility>
#include <algorithm>

#include <cmath>

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;
constexpr int bitsPerPixel = 32;
constexpr int bytesPerPixel = bitsPerPixel / 8;
constexpr std::uint32_t backgroundColor = 0xFF000000;
constexpr std::uint32_t whiteColor = 0xFFFFFFFF;
constexpr Uint32 frameDelayMilliseconds = 16;

struct ScreenPoint
{
    int x;
    int y;
};

struct LifetimeLogger
{
    LifetimeLogger()
    {
        std::cout << "created" << '\n';
    }
    ~LifetimeLogger()
    {
        std::cout << "destroyed" << '\n';
    }
};

double calculateArea(double width, double height)
{
    return width * height;
}

double calculatePerimeter(double width, double height)
{
    return 2 * (width + height);
}

void drawPixel(std::vector<std::uint32_t> &framebuffer, int width, int height, int x, int y, std::uint32_t color)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return;
    }

    const int index = y * width + x;
    framebuffer[index] = color;
}

void drawHorizontalLine(std::vector<std::uint32_t> &framebuffer, int width, int height, int xStart, int xEnd, int y, std::uint32_t color)
{
    if (xStart > xEnd)
    {
        std::swap(xStart, xEnd);
    }

    while (xStart <= xEnd)
    {
        drawPixel(framebuffer, width, height, xStart, y, color);
        xStart++;
    }
}

void drawLine(std::vector<std::uint32_t> &framebuffer, int width, int height, int xStart, int yStart, int xEnd, int yEnd, std::uint32_t color)
{
    const int deltaX = xEnd - xStart;
    const int deltaY = yEnd - yStart;

    const int steps = std::max(std::abs(deltaX), std::abs(deltaY));
    if (steps == 0)
    {
        drawPixel(framebuffer, width, height, xStart, yStart, color);
        return;
    }

    const double xIncrement = static_cast<double>(deltaX) / steps;
    const double yIncrement = static_cast<double>(deltaY) / steps;

    int currentStep = 0;
    double currentX = xStart;
    double currentY = yStart;

    while (currentStep <= steps)
    {
        drawPixel(framebuffer, width, height, static_cast<int>(std::round(currentX)), static_cast<int>(std::round(currentY)), color);

        currentX += xIncrement;
        currentY += yIncrement;
        currentStep++;
    }
}

void drawTriangleOutline(std::vector<std::uint32_t> &framebuffer, int width, int height, const ScreenPoint &a, const ScreenPoint &b, const ScreenPoint &c, std::uint32_t color)
{
    drawLine(framebuffer, width, height, a.x, a.y, b.x, b.y, color);
    drawLine(framebuffer, width, height, b.x, b.y, c.x, c.y, color);
    drawLine(framebuffer, width, height, c.x, c.y, a.x, a.y, color);
}

int main()
{
    const int initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult != 0)
    {
        std::cout << "SDL initialization failed: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "3D Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        0);

    if (window == nullptr)
    {
        std::cout << "Window creation failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    SDL_Surface *windowSurface = SDL_GetWindowSurface(window);

    if (windowSurface == nullptr)
    {
        std::cout << "Window surface creation failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::vector<std::uint32_t> framebuffer(windowWidth * windowHeight, backgroundColor);

    drawPixel(framebuffer, windowWidth, windowHeight, windowWidth / 2, windowHeight / 2, whiteColor);

    std::uint32_t *framebufferPixels = framebuffer.data();
    const int framebufferPitch = windowWidth * bytesPerPixel;

    SDL_Surface *framebufferSurface = SDL_CreateRGBSurfaceWithFormatFrom(
        framebufferPixels,
        windowWidth,
        windowHeight,
        bitsPerPixel,
        framebufferPitch,
        SDL_PIXELFORMAT_ARGB8888);

    if (framebufferSurface == nullptr)
    {
        std::cout << "Frame buffer surface creation failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    drawTriangleOutline(framebuffer, windowWidth, windowHeight, {400, 100}, {150, 500}, {650, 500}, whiteColor);

    bool running = true;

    while (running)
    {
        SDL_Event event{};
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                running = false;

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                drawPixel(framebuffer, windowWidth, windowHeight, event.button.x, event.button.y, whiteColor);
                std::cout << "Mouse coordinates: (" << event.button.x << ", " << event.button.y << ")" << "\n";
            }
        }
        SDL_BlitSurface(framebufferSurface, nullptr, windowSurface, nullptr);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(frameDelayMilliseconds);
    }

    SDL_FreeSurface(framebufferSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
