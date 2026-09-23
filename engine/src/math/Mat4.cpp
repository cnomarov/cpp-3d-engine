#include <engine/math/Mat4.hpp>

#include <cmath>

Mat4 Mat4::identity()
{
    // clang-format off
    return Mat4{
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
     };
    // clang-format on
}

Mat4 Mat4::scaling(const Vec3 &scale)
{
    // clang-format off
    return Mat4{
        scale.x, 0.0, 0.0, 0.0,
        0.0, scale.y, 0.0, 0.0,
        0.0, 0.0, scale.z, 0.0,
        0.0, 0.0, 0.0, 1.0,
    };
    // clang-format on
}

Mat4 Mat4::rotationZ(double radians)
{
    const double sin = std::sin(radians);
    const double cos = std::cos(radians);
    // clang-format off
    return Mat4{
        cos, -sin,  0.0, 0.0,
        sin,  cos,  0.0, 0.0,
        0.0,  0.0,  1.0, 0.0,
        0.0,  0.0,  0.0, 1.0
    };
    // clang-format on
}

Mat4 Mat4::rotationX(double radians)
{
    const double sin = std::sin(radians);
    const double cos = std::cos(radians);
    // clang-format off
    return Mat4{
        1.0, 0.0,  0.0, 0.0,
        0.0, cos, -sin, 0.0,
        0.0, sin,  cos, 0.0,
        0.0, 0.0,  0.0, 1.0,
    };
    // clang-format on
}

Mat4 Mat4::rotationY(double radians)
{
    const double sin = std::sin(radians);
    const double cos = std::cos(radians);
    // clang-format off
    return Mat4{
        cos,  0.0, sin, 0.0,
        0.0,  1.0, 0.0, 0.0,
        -sin, 0.0, cos, 0.0,
        0.0,  0.0, 0.0, 1.0,
    };
    // clang-format on
}

Mat4 Mat4::translation(const Vec3 &offset)
{
    // clang-format off
    return Mat4{
        1.0, 0.0, 0.0, offset.x,
        0.0, 1.0, 0.0, offset.y,
        0.0, 0.0, 1.0, offset.z,
        0.0, 0.0, 0.0, 1.0
    };
    // clang-format on
}

Vec4 Mat4::operator*(const Vec4 &value) const
{
    return Vec4{
        m00 * value.x + m01 * value.y + m02 * value.z + m03 * value.w,
        m10 * value.x + m11 * value.y + m12 * value.z + m13 * value.w,
        m20 * value.x + m21 * value.y + m22 * value.z + m23 * value.w,
        m30 * value.x + m31 * value.y + m32 * value.z + m33 * value.w};
}

Mat4 Mat4::operator*(const Mat4 &other) const
{
    const double c00 = m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30;
    const double c01 = m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31;
    const double c02 = m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32;
    const double c03 = m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33;
    const double c10 = m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30;
    const double c11 = m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31;
    const double c12 = m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32;
    const double c13 = m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33;
    const double c20 = m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30;
    const double c21 = m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31;
    const double c22 = m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32;
    const double c23 = m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33;
    const double c30 = m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30;
    const double c31 = m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31;
    const double c32 = m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32;
    const double c33 = m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33;

    // clang-format off
    return Mat4{ 
        c00, c01, c02, c03,
        c10, c11, c12, c13,
        c20, c21, c22, c23,
        c30, c31, c32, c33
    };
    // clang-format on
}

Mat4 Mat4::transposed() const
{
    // clang-format off
    return Mat4{ 
        m00, m10, m20, m30,
        m01, m11, m21, m31,
        m02, m12, m22, m32,
        m03, m13, m23, m33
    };
    // clang-format on
}