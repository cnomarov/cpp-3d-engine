#pragma once

#include <engine/math/Vec3.hpp>

struct Quaternion
{
    double x;
    double y;
    double z;
    double w;

    static Quaternion identity();
    static Quaternion fromAxisAngle(const Vec3 &axis, double radians);
    static Quaternion fromEulerXYZ(const Vec3 &radians);
    double length() const;
    Vec3 rotated(const Vec3 &vector) const;
    Vec3 toEulerXYZ() const;
    Quaternion normalized() const;
    Quaternion conjugated() const;
    Quaternion inverse() const;
    Quaternion operator*(const Quaternion &other) const;
    bool approximatelyEquals(const Quaternion &other, double epsilon) const;
};
