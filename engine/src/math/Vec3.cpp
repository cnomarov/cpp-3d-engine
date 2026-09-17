#include <engine/math/Vec3.hpp>

#include <cassert>
#include <cmath>

Vec3 Vec3::operator+(const Vec3 &other) const
{
    return Vec3{
        x + other.x,
        y + other.y,
        z + other.z};
}

Vec3 Vec3::operator-(const Vec3 &other) const
{
    return Vec3{
        x - other.x,
        y - other.y,
        z - other.z};
}

Vec3 Vec3::operator*(double scalar) const
{
    return Vec3{
        x * scalar,
        y * scalar,
        z * scalar};
}

Vec3 Vec3::operator/(double scalar) const
{
    assert(scalar != 0.0);
    return Vec3{
        x / scalar,
        y / scalar,
        z / scalar};
}

Vec3 Vec3::operator-() const
{
    return {
        -x,
        -y,
        -z};
}

double Vec3::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalized() const
{
    const double vectorLength = length();
    if (vectorLength == 0.0)
    {
        return Vec3{0.0, 0.0, 0.0};
    }
    return Vec3{x / vectorLength, y / vectorLength, z / vectorLength};
}

bool Vec3::approximatelyEquals(const Vec3 &other, double epsilon) const
{
    assert(epsilon >= 0.0);
    return std::abs(x - other.x) <= epsilon && std::abs(y - other.y) <= epsilon && std::abs(z - other.z) <= epsilon;
}

double Vec3::dot(const Vec3 &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3 &other) const
{
    return Vec3{
        y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
}

double Vec3::distanceTo(const Vec3 &other) const
{
    return (*this - other).length();
}