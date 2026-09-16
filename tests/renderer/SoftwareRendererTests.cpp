#include <engine/renderer/SoftwareRenderer.hpp>

#include <cassert>
#include <cstdint>

constexpr std::uint32_t black = 0xFF000000;
constexpr std::uint32_t white = 0xFFFFFFFF;

std::uint32_t pixelAt(SoftwareRenderer &renderer, int width, const ScreenPoint &point)
{
    const int index = point.y * width + point.x;
    return renderer.data()[index];
}

void testInitialColorAndPixelDrawing()
{
    constexpr int width = 4;
    constexpr int height = 3;
    SoftwareRenderer renderer{width, height, black};

    for (int index = 0; index < width * height; ++index)
    {
        assert(renderer.data()[index] == black);
    }

    const ScreenPoint point{2, 1};
    renderer.drawPixel(point, white);
    assert(pixelAt(renderer, width, point) == white);
}

void testPixelOutsideFramebufferIsIgnored()
{
    constexpr int width = 4;
    constexpr int height = 3;
    SoftwareRenderer renderer{width, height, black};

    renderer.drawPixel({-1, 0}, white);
    renderer.drawPixel({width, 0}, white);
    renderer.drawPixel({0, -1}, white);
    renderer.drawPixel({0, height}, white);

    for (int index = 0; index < width * height; ++index)
    {
        assert(renderer.data()[index] == black);
    }
}

void testLineEndpointsAndDirections()
{
    constexpr int width = 7;
    constexpr int height = 7;
    SoftwareRenderer renderer{width, height, black};

    renderer.drawLine({1, 1}, {5, 3}, white);
    assert(pixelAt(renderer, width, {1, 1}) == white);
    assert(pixelAt(renderer, width, {3, 2}) == white);
    assert(pixelAt(renderer, width, {5, 3}) == white);

    renderer.drawLine({5, 5}, {1, 3}, white);
    assert(pixelAt(renderer, width, {5, 5}) == white);
    assert(pixelAt(renderer, width, {1, 3}) == white);

    renderer.drawLine({6, 1}, {6, 5}, white);
    assert(pixelAt(renderer, width, {6, 1}) == white);
    assert(pixelAt(renderer, width, {6, 3}) == white);
    assert(pixelAt(renderer, width, {6, 5}) == white);

    renderer.drawLine({0, 6}, {0, 6}, white);
    assert(pixelAt(renderer, width, {0, 6}) == white);
}

void testTriangleOutlineConnectsAllVertices()
{
    constexpr int width = 7;
    constexpr int height = 6;
    SoftwareRenderer renderer{width, height, black};

    const ScreenPoint top{3, 0};
    const ScreenPoint left{0, 4};
    const ScreenPoint right{6, 4};
    renderer.drawTriangleOutline(top, left, right, white);

    assert(pixelAt(renderer, width, top) == white);
    assert(pixelAt(renderer, width, left) == white);
    assert(pixelAt(renderer, width, right) == white);
    assert(pixelAt(renderer, width, {3, 4}) == white);
    assert(pixelAt(renderer, width, {1, 3}) == white);
    assert(pixelAt(renderer, width, {5, 3}) == white);
}

int main()
{
    testInitialColorAndPixelDrawing();
    testPixelOutsideFramebufferIsIgnored();
    testLineEndpointsAndDirections();
    testTriangleOutlineConnectsAllVertices();
    return 0;
}
