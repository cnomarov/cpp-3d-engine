#pragma once

#include <engine/math/Vec3.hpp>
#include <engine/math/Mat3.hpp>

struct Quaternion
{
    double x;
    double y;
    double z;
    double w;

    static Quaternion identity();
    static Quaternion fromAxisAngle(const Vec3 &axis, double radians);
    static Quaternion fromEulerXYZ(const Vec3 &radians);
    static Quaternion fromMat3(const Mat3 &matrix);
    double length() const;
    double dot(const Quaternion &other) const;
    Vec3 rotated(const Vec3 &vector) const;
    Vec3 toEulerXYZ() const;
    Mat3 toMat3() const;
    Quaternion normalized() const;
    Quaternion conjugated() const;
    Quaternion inverse() const;
    Quaternion operator-() const;
    Quaternion operator+(const Quaternion &other) const;
    Quaternion operator*(const Quaternion &other) const;
    Quaternion operator*(double scalar) const;
    Quaternion differenceTo(const Quaternion &target) const;
    Quaternion nlerpTo(const Quaternion &target, double t) const;
    Quaternion slerpTo(const Quaternion &target, double t) const;
    bool approximatelyEquals(const Quaternion &other, double epsilon) const;
};
