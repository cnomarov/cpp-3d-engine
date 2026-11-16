#include <iostream>

#include <engine/math/Quaternion.hpp>
#include <engine/renderer/SoftwareRenderer.hpp>
#include <engine/math/Mat4.hpp>
#include <engine/math/Vec2.hpp>
#include <engine/camera/Camera.hpp>
#include <SDL.h>
#include <cstdint>
#include <array>

#include <algorithm>
#include <cmath>
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

    SoftwareRenderer renderer{windowWidth, windowHeight, backgroundColor};

    std::uint32_t *framebufferPixels = renderer.data();
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

    SDL_SetRelativeMouseMode(SDL_TRUE);

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
    const double cameraSpeed = 3.0;

    const Vec3 orbitTarget{2.0, 3.0, 4.0};
    const double orbitRadius = 5;
    double orbitAngle = std::numbers::pi / 4;
    const double orbitAngularSpeed = 0.5;

    const double orbitX = orbitTarget.x + orbitRadius * std::sin(orbitAngle);
    const double orbitZ = orbitTarget.z - orbitRadius * std::cos(orbitAngle);
    const Vec3 orbitPosition{orbitX, orbitTarget.y, orbitZ};

    Camera camera{
        .position = orbitPosition,
        .yawRadians = -orbitAngle,
        .pitchRadians = 0.0,
        .verticalFovRadians = std::numbers::pi / 2,
        .nearPlane = 0.1,
        .farPlane = 100.0,
    };

    const double maxCameraPitch = std::numbers::pi / 2.0 - 0.01;

    Quaternion cubeOrientation = Quaternion::fromAxisAngle({0.0, 1.0, 0.0}, 0.5);

    const double zoomStep = std::numbers::pi / 36;
    const double minFov = std::numbers::pi / 9;
    const double maxFov = std::numbers::pi * (2.0 / 3.0);

    const double aspectRatio = static_cast<double>(windowWidth) / static_cast<double>(windowHeight);

    const ScreenPoint center{
        windowWidth / 2,
        windowHeight / 2};

    bool running = true;

    Uint64 previousFrameTicks = SDL_GetTicks64();
    bool orbitMode = true;

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
                renderer.drawPixel({event.button.x, event.button.y}, whiteColor);
                std::cout << "Mouse coordinates: (" << event.button.x << ", " << event.button.y << ")" << "\n";
            }

            if (event.type == SDL_MOUSEMOTION)
            {
                if ((event.motion.state & SDL_BUTTON_LMASK) != 0)
                {
                    const double deltaYawRadians = static_cast<double>(event.motion.xrel) * mouseSensitivity;
                    const double deltaPitchRadians = static_cast<double>(event.motion.yrel) * mouseSensitivity;
                    const Quaternion deltaPitch = Quaternion::fromAxisAngle({1.0, 0.0, 0.0}, deltaPitchRadians);
                    const Quaternion deltaYaw = Quaternion::fromAxisAngle({0.0, 1.0, 0.0}, deltaYawRadians);
                    cubeOrientation = (deltaYaw * cubeOrientation * deltaPitch).normalized();
                }
                else
                {
                    camera.yawRadians += static_cast<double>(event.motion.xrel) * mouseSensitivity;
                    camera.pitchRadians += static_cast<double>(event.motion.yrel) * mouseSensitivity;
                    camera.pitchRadians = std::clamp(camera.pitchRadians, -maxCameraPitch, maxCameraPitch);
                }
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_R)
            {
                cubeOrientation = cubeOrientation.slerpTo(Quaternion::identity(), 0.5);
            }

            if (event.type == SDL_MOUSEWHEEL)
            {
                camera.verticalFovRadians = std::clamp(camera.verticalFovRadians - static_cast<double>(event.wheel.y) * zoomStep, minFov, maxFov);
            }
            if (event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.scancode == SDL_SCANCODE_O)
            {
                orbitMode = !orbitMode;
            }
        }

        const Uint64 currentFrameTicks = SDL_GetTicks64();
        const Uint64 elapsedMilliseconds = currentFrameTicks - previousFrameTicks;
        const double deltaTimeSeconds = static_cast<double>(elapsedMilliseconds) / 1000.0;
        previousFrameTicks = currentFrameTicks;

        const double cameraMovement = cameraSpeed * deltaTimeSeconds;
        const Vec3 cameraForward = {std::sin(camera.yawRadians), 0, std::cos(camera.yawRadians)};
        const Vec3 worldUp{0.0, 1.0, 0.0};
        const Vec3 cameraRight = worldUp.cross(cameraForward);

        const Uint8 *keyboardState = SDL_GetKeyboardState(nullptr);

        if (keyboardState[SDL_SCANCODE_W])
        {
            camera.position = camera.position + cameraForward * cameraMovement;
        }
        if (keyboardState[SDL_SCANCODE_S])
        {
            camera.position = camera.position - cameraForward * cameraMovement;
        }
        if (keyboardState[SDL_SCANCODE_A])
        {
            camera.position = camera.position - cameraRight * cameraMovement;
        }
        if (keyboardState[SDL_SCANCODE_D])
        {
            camera.position = camera.position + cameraRight * cameraMovement;
        }
        if (keyboardState[SDL_SCANCODE_LEFT])
        {
            orbitAngle -= orbitAngularSpeed * deltaTimeSeconds;
        }
        if (keyboardState[SDL_SCANCODE_RIGHT])
        {
            orbitAngle += orbitAngularSpeed * deltaTimeSeconds;
        }
        if (keyboardState[SDL_SCANCODE_SPACE])
        {
            camera.position = camera.position + worldUp * cameraMovement;
        }
        if (keyboardState[SDL_SCANCODE_LCTRL])
        {
            camera.position = camera.position - worldUp * cameraMovement;
        }

        if (orbitMode)
        {
            const double currentOrbitX = orbitTarget.x + orbitRadius * std::sin(orbitAngle);
            const double currentOrbitZ = orbitTarget.z - orbitRadius * std::cos(orbitAngle);
            camera.position = {currentOrbitX, orbitTarget.y, currentOrbitZ};
            camera.yawRadians = -orbitAngle;
        }

        std::fill_n(renderer.data(), windowWidth * windowHeight, backgroundColor);

        // cube matrices

        const Mat4 viewMatrix = camera.viewMatrix();

        const Mat4 modelMatrix = Mat4::translation({2.0, 3.0, 4.0});
        const Mat4 projectionMatrix = camera.projectionMatrix(aspectRatio);

        // cube view operations

        for (std::size_t index = 0; index < cubeVertices.size(); ++index)
        {
            const Vec3 rotatedVertex = cubeOrientation.rotated(cubeVertices[index]);
            const Vec4 objectVertex = Vec4::fromPoint(rotatedVertex);
            const Vec4 worldVertex = modelMatrix * objectVertex;
            cubeWorldVertices[index] = worldVertex;
        }

        for (std::size_t index = 0; index < cubeWorldVertices.size(); ++index)
        {
            const Vec4 viewVertex = viewMatrix * cubeWorldVertices[index];
            cubeViewVertices[index] = viewVertex;
        }

        for (std::size_t index = 0; index < cubeViewVertices.size(); ++index)
        {
            const Vec4 clipVertex = projectionMatrix * cubeViewVertices[index];
            const double projectedX = clipVertex.x / clipVertex.w;
            const double projectedY = clipVertex.y / clipVertex.w;
            cubeProjectedVertices[index] = {projectedX, projectedY};
        }

        for (std::size_t index = 0; index < cubeProjectedVertices.size(); ++index)
        {
            const ScreenPoint screenPoint{
                center.x + static_cast<int>(std::round(cubeProjectedVertices[index].x * static_cast<double>(windowWidth) / 2.0)),
                center.y - static_cast<int>(std::round(cubeProjectedVertices[index].y * static_cast<double>(windowHeight) / 2.0)),
            };
            cubeScreenVertices[index] = screenPoint;
        }

        for (const Edge edge : nearFaceEdges)
        {
            renderer.drawLine(
                cubeScreenVertices[edge.start],
                cubeScreenVertices[edge.end],
                whiteColor);
        }

        for (const Edge edge : nearFaceEdges)
        {
            renderer.drawLine(
                cubeScreenVertices[edge.start + 4],
                cubeScreenVertices[edge.end + 4],
                whiteColor);
        }

        for (std::size_t index = 0; index < 4; ++index)
        {
            renderer.drawLine(
                cubeScreenVertices[index],
                cubeScreenVertices[index + 4],
                whiteColor);
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
