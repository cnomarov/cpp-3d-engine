#include <engine/math/Quaternion.hpp>
#include <engine/renderer/SoftwareRenderer.hpp>

#include <SDL.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;
constexpr int bitsPerPixel = 32;
constexpr int bytesPerPixel = bitsPerPixel / 8;
constexpr std::uint32_t backgroundColor = 0xFF000000;
constexpr std::uint32_t whiteColor = 0xFFFFFFFF;
constexpr Uint32 frameDelayMilliseconds = 16;

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL initialization failed: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Quaternion Demo",
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

    SoftwareRenderer renderer{windowWidth, windowHeight, backgroundColor};
    SDL_Surface *framebufferSurface = SDL_CreateRGBSurfaceWithFormatFrom(
        renderer.data(),
        windowWidth,
        windowHeight,
        bitsPerPixel,
        windowWidth * bytesPerPixel,
        SDL_PIXELFORMAT_ARGB8888);

    if (framebufferSurface == nullptr)
    {
        std::cout << "Framebuffer surface creation failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    const ScreenPoint center{windowWidth / 2, windowHeight / 2};
    const double arrowLength = 150.0;

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
        }

        std::fill_n(renderer.data(), windowWidth * windowHeight, backgroundColor);

        const double seconds = static_cast<double>(SDL_GetTicks()) / 1000.0;
        const Quaternion rotation = Quaternion::fromAxisAngle({0.0, 0.0, 1.0}, seconds);
        const Vec3 rotatedDirection = rotation.rotated({1.0, 0.0, 0.0});
        const ScreenPoint end{
            center.x + static_cast<int>(std::round(rotatedDirection.x * arrowLength)),
            center.y - static_cast<int>(std::round(rotatedDirection.y * arrowLength))};

        renderer.drawLine(center, end, whiteColor);

        SDL_BlitSurface(framebufferSurface, nullptr, windowSurface, nullptr);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(frameDelayMilliseconds);
    }

    SDL_FreeSurface(framebufferSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
