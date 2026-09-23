#include <engine/math/Mat3.hpp>

#include <cmath>

Mat3 Mat3::identity()
{
    // clang-format off
    return Mat3{
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
     };
    // clang-format on
}

Mat3 Mat3::scaling(const Vec3 &scale)
{
    // clang-format off
    return Mat3{
        scale.x, 0.0, 0.0,
        0.0, scale.y, 0.0,
        0.0, 0.0, scale.z
    };
    // clang-format on
}

Mat3 Mat3::rotationZ(double radians)
{
    const double sin = std::sin(radians);
    const double cos = std::cos(radians);
    // clang-format off
    return Mat3{
        cos, -sin,  0,
        sin,  cos,  0,
        0,     0,   1
    };
    // clang-format on
}

Mat3 Mat3::rotationX(double radians)
{
    const double sin = std::sin(radians);
    const double cos = std::cos(radians);
    // clang-format off
    return Mat3{
        1,   0,    0,
        0, cos,-sin,
        0, sin, cos
    };
    // clang-format on
}

Mat3 Mat3::rotationY(double radians)
{
    const double sin = std::sin(radians);
    const double cos = std::cos(radians);
    // clang-format off
    return Mat3{
        cos, 0,  sin,
        0,   1,    0,
        -sin, 0, cos
    };
    // clang-format on
}

Vec3 Mat3::operator*(const Vec3 &value) const
{
    return Vec3{
        m00 * value.x + m01 * value.y + m02 * value.z,
        m10 * value.x + m11 * value.y + m12 * value.z,
        m20 * value.x + m21 * value.y + m22 * value.z,
    };
}

Mat3 Mat3::operator*(const Mat3 &other) const
{
    const double c00 = m00 * other.m00 + m01 * other.m10 + m02 * other.m20;
    const double c01 = m00 * other.m01 + m01 * other.m11 + m02 * other.m21;
    const double c02 = m00 * other.m02 + m01 * other.m12 + m02 * other.m22;
    const double c10 = m10 * other.m00 + m11 * other.m10 + m12 * other.m20;
    const double c11 = m10 * other.m01 + m11 * other.m11 + m12 * other.m21;
    const double c12 = m10 * other.m02 + m11 * other.m12 + m12 * other.m22;
    const double c20 = m20 * other.m00 + m21 * other.m10 + m22 * other.m20;
    const double c21 = m20 * other.m01 + m21 * other.m11 + m22 * other.m21;
    const double c22 = m20 * other.m02 + m21 * other.m12 + m22 * other.m22;

    // clang-format off
    return Mat3{ 
        c00, c01, c02,
        c10, c11, c12,
        c20, c21, c22
    };
    // clang-format on
}

Mat3 Mat3::transposed() const
{
    // clang-format off
    return Mat3{ 
        m00, m10, m20,
        m01, m11, m21,
        m02, m12, m22
    };
    // clang-format on
}