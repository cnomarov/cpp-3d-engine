#include <engine/math/Vec2.hpp>

#include <cassert>
#include <cmath>

double Vec2::length() const
{
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::operator+(const Vec2 &other) const
{
    return Vec2{
        x + other.x,
        y + other.y};
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
    return Vec2{
        x - other.x,
        y - other.y};
}

Vec2 Vec2::operator*(double scalar) const
{
    return Vec2{
        x * scalar,
        y * scalar};
}

Vec2 Vec2::operator/(double scalar) const
{
    assert(scalar != 0.0);
    return Vec2{
        x / scalar,
        y / scalar};
}

Vec2 Vec2::operator-() const
{
    return Vec2{
        -x,
        -y};
}

Vec2 Vec2::normalized() const
{
    const double vectorLength = length();
    if (vectorLength == 0.0)
    {
        return Vec2{0.0, 0.0};
    }
    return Vec2{x / vectorLength, y / vectorLength};
}

double Vec2::dot(const Vec2 &other) const
{
    return x * other.x + y * other.y;
}

double Vec2::distanceTo(const Vec2 &other) const
{
    return (*this - other).length();
}

Vec2 Vec2::projectedOnto(const Vec2 &axis) const
{
    const double axisDot = axis.dot(axis);
    assert(axisDot != 0.0);

    return axis * (dot(axis) / axisDot);
}

bool Vec2::approximatelyEquals(const Vec2 &other, double epsilon) const
{
    assert(epsilon >= 0.0);
    return std::abs(x - other.x) <= epsilon && std::abs(y - other.y) <= epsilon;
}
