#pragma once

#include <engine/math/Vec4.hpp>
#include <engine/math/Vec3.hpp>

struct Mat4
{
    double m00;
    double m01;
    double m02;
    double m03;
    double m10;
    double m11;
    double m12;
    double m13;
    double m20;
    double m21;
    double m22;
    double m23;
    double m30;
    double m31;
    double m32;
    double m33;

    static Mat4 identity();
    static Mat4 scaling(const Vec3 &scale);
    static Mat4 rotationZ(double radians);
    static Mat4 rotationX(double radians);
    static Mat4 rotationY(double radians);
    static Mat4 translation(const Vec3 &offset);
    Vec4 operator*(const Vec4 &value) const;
    Mat4 operator*(const Mat4 &other) const;
    Mat4 transposed() const;
};