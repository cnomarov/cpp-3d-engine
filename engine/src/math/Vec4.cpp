#include <engine/math/Vec4.hpp>

Vec4 Vec4::fromPoint(const Vec3 &value)
{
    return Vec4{
        value.x,
        value.y,
        value.z,
        1.0};
}

Vec4 Vec4::fromDirection(const Vec3 &value)
{
    return Vec4{
        value.x,
        value.y,
        value.z,
        0.0};
}