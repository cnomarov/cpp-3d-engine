#pragma once

struct Vec3
{
    double x;
    double y;
    double z;

    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator*(double scalar) const;
    Vec3 operator/(double scalar) const;
    Vec3 operator-() const;
    double length() const;
    Vec3 normalized() const;
    double dot(const Vec3 &other) const;
    Vec3 cross(const Vec3 &other) const;
    double distanceTo(const Vec3 &other) const;
    bool approximatelyEquals(const Vec3 &other, double epsilon) const;
};
