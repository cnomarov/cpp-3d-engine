#pragma once

#include <engine/math/Vec3.hpp>

struct Mat3
{
    double m00;
    double m01;
    double m02;
    double m10;
    double m11;
    double m12;
    double m20;
    double m21;
    double m22;

    static Mat3 identity();
    static Mat3 scaling(const Vec3 &scale);
    static Mat3 rotationZ(double radians);
    static Mat3 rotationX(double radians);
    static Mat3 rotationY(double radians);
    Vec3 operator*(const Vec3 &value) const;
    Mat3 operator*(const Mat3 &other) const;
    Mat3 transposed() const;
};