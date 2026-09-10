#pragma once

struct Vec2
{
    double x;
    double y;
    Vec2 operator+(const Vec2 &other) const;

    Vec2 operator-(const Vec2 &other) const;

    Vec2 operator*(double scalar) const;

    Vec2 operator/(double scalar) const;

    Vec2 operator-() const;

    double length() const;

    Vec2 normalized() const;

    double dot(const Vec2 &other) const;

    double distanceTo(const Vec2 &other) const;

    Vec2 projectedOnto(const Vec2 &axis) const;

    bool approximatelyEquals(const Vec2 &other, double epsilon) const;
};