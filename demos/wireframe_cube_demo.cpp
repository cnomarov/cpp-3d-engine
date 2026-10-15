#include <engine/math/Mat4.hpp>
#include <engine/math/Quaternion.hpp>
#include <engine/math/Vec2.hpp>
#include <engine/renderer/SoftwareRenderer.hpp>

#include <SDL.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numbers>

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;
constexpr int bitsPerPixel = 32;
constexpr int bytesPerPixel = bitsPerPixel / 8;
constexpr std::uint32_t backgroundColor = 0xFF000000;
constexpr std::uint32_t whiteColor = 0xFFFFFFFF;
constexpr Uint32 frameDelayMilliseconds = 16;

struct Edge
{
    std::size_t start;
    std::size_t end;
};

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL initialization failed: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Wireframe Cube Demo",
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

    const std::array<Vec3, 8> cubeVertices{
        Vec3{-1.0, -1.0, -1.0},
        Vec3{1.0, -1.0, -1.0},
        Vec3{1.0, 1.0, -1.0},
        Vec3{-1.0, 1.0, -1.0},
        Vec3{-1.0, -1.0, 1.0},
        Vec3{1.0, -1.0, 1.0},
        Vec3{1.0, 1.0, 1.0},
        Vec3{-1.0, 1.0, 1.0},
    };

    const std::array<Edge, 4> nearFaceEdges{
        Edge{0, 1},
        Edge{1, 2},
        Edge{2, 3},
        Edge{3, 0}};

    std::array<Vec4, 8> cubeWorldVertices{};
    std::array<Vec4, 8> cubeViewVertices{};
    std::array<Vec2, 8> cubeProjectedVertices{};
    std::array<ScreenPoint, 8> cubeScreenVertices{};

    const double mouseSensitivity = 0.01;
    Quaternion cubeOrientation = Quaternion::fromAxisAngle({0.0, 1.0, 0.0}, 0.5);

    const Vec3 cameraPosition{2.0, 3.0, 0.0};
    const Mat4 viewMatrix = Mat4::translation(-cameraPosition);

    double verticalFovRadians = std::numbers::pi / 2.0;
    const double zoomStep = std::numbers::pi / 36.0;
    const double minFov = std::numbers::pi / 9.0;
    const double maxFov = std::numbers::pi * (2.0 / 3.0);
    const double aspectRatio = static_cast<double>(windowWidth) / static_cast<double>(windowHeight);
    const double nearPlane = 0.1;
    const double farPlane = 100.0;

    const ScreenPoint center{windowWidth / 2, windowHeight / 2};

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

            if (event.type == SDL_MOUSEMOTION && (event.motion.state & SDL_BUTTON_LMASK) != 0)
            {
                const double deltaYawRadians = static_cast<double>(event.motion.xrel) * mouseSensitivity;
                const double deltaPitchRadians = static_cast<double>(event.motion.yrel) * mouseSensitivity;
                const Quaternion deltaPitch = Quaternion::fromAxisAngle({1.0, 0.0, 0.0}, deltaPitchRadians);
                const Quaternion deltaYaw = Quaternion::fromAxisAngle({0.0, 1.0, 0.0}, deltaYawRadians);
                cubeOrientation = (deltaYaw * cubeOrientation * deltaPitch).normalized();
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_R)
            {
                cubeOrientation = cubeOrientation.slerpTo(Quaternion::identity(), 0.5);
            }

            if (event.type == SDL_MOUSEWHEEL)
            {
                verticalFovRadians = std::clamp(
                    verticalFovRadians - static_cast<double>(event.wheel.y) * zoomStep,
                    minFov,
                    maxFov);
            }
        }

        std::fill_n(renderer.data(), windowWidth * windowHeight, backgroundColor);

        const Mat4 modelMatrix = Mat4::translation({2.0, 3.0, 4.0});
        const Mat4 projectionMatrix = Mat4::perspective(verticalFovRadians, aspectRatio, nearPlane, farPlane);

        for (std::size_t index = 0; index < cubeVertices.size(); ++index)
        {
            const Vec3 rotatedVertex = cubeOrientation.rotated(cubeVertices[index]);
            cubeWorldVertices[index] = modelMatrix * Vec4::fromPoint(rotatedVertex);
            cubeViewVertices[index] = viewMatrix * cubeWorldVertices[index];

            const Vec4 clipVertex = projectionMatrix * cubeViewVertices[index];
            cubeProjectedVertices[index] = {
                clipVertex.x / clipVertex.w,
                clipVertex.y / clipVertex.w};

            cubeScreenVertices[index] = {
                center.x + static_cast<int>(std::round(cubeProjectedVertices[index].x * static_cast<double>(windowWidth) / 2.0)),
                center.y - static_cast<int>(std::round(cubeProjectedVertices[index].y * static_cast<double>(windowHeight) / 2.0))};
        }

        for (const Edge edge : nearFaceEdges)
        {
            renderer.drawLine(cubeScreenVertices[edge.start], cubeScreenVertices[edge.end], whiteColor);
            renderer.drawLine(cubeScreenVertices[edge.start + 4], cubeScreenVertices[edge.end + 4], whiteColor);
        }

        for (std::size_t index = 0; index < 4; ++index)
        {
            renderer.drawLine(cubeScreenVertices[index], cubeScreenVertices[index + 4], whiteColor);
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
