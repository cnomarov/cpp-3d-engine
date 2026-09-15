#include <iostream>

#include <engine/math/Vec2.hpp>
#include <memory>
#include <vector>
#include <fstream>
#include <SDL.h>
#include <cstdint>

#include <cmath>

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;
constexpr int bitsPerPixel = 32;
constexpr int bytesPerPixel = bitsPerPixel / 8;
constexpr std::uint32_t backgroundColor = 0xFF000000;
constexpr std::uint32_t whiteColor = 0xFFFFFFFF;
constexpr Uint32 frameDelayMilliseconds = 16;

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
