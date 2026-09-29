#include <engine/math/Quaternion.hpp>

#include <cassert>
#include <cmath>
#include <algorithm>

Quaternion Quaternion::identity()
{
    return Quaternion{0.0, 0.0, 0.0, 1.0};
}

Quaternion Quaternion::fromAxisAngle(const Vec3 &axis, double radians)
{
    assert(axis.length() != 0);
    const Vec3 normalizedAxis = axis.normalized();
    const double halfRadians = radians / 2;

    const double newX = normalizedAxis.x * std::sin(halfRadians);
    const double newY = normalizedAxis.y * std::sin(halfRadians);
    const double newZ = normalizedAxis.z * std::sin(halfRadians);
    const double newW = std::cos(halfRadians);

    return Quaternion{newX, newY, newZ, newW};
}

Quaternion Quaternion::fromEulerXYZ(const Vec3 &radians)
{
    const Quaternion rotationX = Quaternion::fromAxisAngle({1.0, 0.0, 0.0}, radians.x);
    const Quaternion rotationY = Quaternion::fromAxisAngle({0.0, 1.0, 0.0}, radians.y);
    const Quaternion rotationZ = Quaternion::fromAxisAngle({0.0, 0.0, 1.0}, radians.z);

    return rotationZ * rotationY * rotationX;
}

Quaternion Quaternion::fromMat3(const Mat3 &matrix)
{
    const double trace = matrix.m00 + matrix.m11 + matrix.m22;

    if (trace > 0.0)
    {
        const double s = 2.0 * std::sqrt(trace + 1.0);
        const double w = s / 4.0;
        const double x = (matrix.m21 - matrix.m12) / s;
        const double y = (matrix.m02 - matrix.m20) / s;
        const double z = (matrix.m10 - matrix.m01) / s;

        return Quaternion{x, y, z, w}.normalized();
    }

    if (matrix.m00 >= matrix.m11 && matrix.m00 >= matrix.m22)
    {
        const double s = 2.0 * std::sqrt(1.0 + matrix.m00 - matrix.m11 - matrix.m22);
        const double w = (matrix.m21 - matrix.m12) / s;
        const double x = s / 4.0;
        const double y = (matrix.m01 + matrix.m10) / s;
        const double z = (matrix.m02 + matrix.m20) / s;

        return Quaternion{x, y, z, w}.normalized();
    }

    if (matrix.m11 >= matrix.m00 && matrix.m11 >= matrix.m22)
    {
        const double s = 2.0 * std::sqrt(1.0 + matrix.m11 - matrix.m00 - matrix.m22);
        const double w = (matrix.m02 - matrix.m20) / s;
        const double x = (matrix.m01 + matrix.m10) / s;
        const double y = s / 4.0;
        const double z = (matrix.m12 + matrix.m21) / s;

        return Quaternion{x, y, z, w}.normalized();
    }

    else
    {
        const double s = 2.0 * std::sqrt(1.0 + matrix.m22 - matrix.m00 - matrix.m11);
        const double w = (matrix.m10 - matrix.m01) / s;
        const double x = (matrix.m02 + matrix.m20) / s;
        const double y = (matrix.m12 + matrix.m21) / s;
        const double z = s / 4.0;

        return Quaternion{x, y, z, w}.normalized();
    }
}

double Quaternion::length() const
{
    return std::sqrt(x * x + y * y + z * z + w * w);
}

double Quaternion::dot(const Quaternion &other) const
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Vec3 Quaternion::rotated(const Vec3 &vector) const
{
    const Quaternion p{vector.x, vector.y, vector.z, 0};
    const Quaternion result = (*this) * p * inverse();

    return Vec3{result.x, result.y, result.z};
}

Vec3 Quaternion::toEulerXYZ() const
{
    const Quaternion normalizedQuat = normalized();
    const double radiansX = std::atan2(2.0 * (normalizedQuat.w * normalizedQuat.x + normalizedQuat.y * normalizedQuat.z), 1.0 - 2.0 * (normalizedQuat.x * normalizedQuat.x + normalizedQuat.y * normalizedQuat.y));
    const double sinY = 2.0 * (normalizedQuat.w * normalizedQuat.y - normalizedQuat.z * normalizedQuat.x);
    const double clampedSinY = std::clamp(sinY, -1.0, 1.0);
    const double radiansY = std::asin(clampedSinY);
    const double radiansZ = std::atan2(2.0 * (normalizedQuat.w * normalizedQuat.z + normalizedQuat.x * normalizedQuat.y), 1.0 - 2.0 * (normalizedQuat.y * normalizedQuat.y + normalizedQuat.z * normalizedQuat.z));

    return Vec3{radiansX, radiansY, radiansZ};
}

Mat3 Quaternion::toMat3() const
{
    const Quaternion normalizedQuat = normalized();

    const double m00 = 1.0 - 2.0 * (normalizedQuat.y * normalizedQuat.y + normalizedQuat.z * normalizedQuat.z);
    const double m01 = 2.0 * (normalizedQuat.x * normalizedQuat.y - normalizedQuat.z * normalizedQuat.w);
    const double m02 = 2.0 * (normalizedQuat.x * normalizedQuat.z + normalizedQuat.y * normalizedQuat.w);
    const double m10 = 2.0 * (normalizedQuat.x * normalizedQuat.y + normalizedQuat.z * normalizedQuat.w);
    const double m11 = 1 - 2 * (normalizedQuat.x * normalizedQuat.x + normalizedQuat.z * normalizedQuat.z);
    const double m12 = 2 * (normalizedQuat.y * normalizedQuat.z - normalizedQuat.x * normalizedQuat.w);
    const double m20 = 2 * (normalizedQuat.x * normalizedQuat.z - normalizedQuat.y * normalizedQuat.w);
    const double m21 = 2 * (normalizedQuat.y * normalizedQuat.z + normalizedQuat.x * normalizedQuat.w);
    const double m22 = 1 - 2 * (normalizedQuat.x * normalizedQuat.x + normalizedQuat.y * normalizedQuat.y);

    return Mat3{m00, m01, m02, m10, m11, m12, m20, m21, m22};
}

Quaternion Quaternion::normalized() const
{
    const double quaternionLength = length();
    assert(quaternionLength != 0);

    return Quaternion{x / quaternionLength, y / quaternionLength, z / quaternionLength, w / quaternionLength};
}

Quaternion Quaternion::conjugated() const
{
    return Quaternion{-x, -y, -z, w};
}

Quaternion Quaternion::inverse() const
{
    const double squaredLength = x * x + y * y + z * z + w * w;
    assert(squaredLength != 0);
    const Quaternion conjugatedQuat = conjugated();
    return Quaternion{conjugatedQuat.x / squaredLength, conjugatedQuat.y / squaredLength, conjugatedQuat.z / squaredLength, conjugatedQuat.w / squaredLength};
}

Quaternion Quaternion::operator-() const
{
    return Quaternion{-x, -y, -z, -w};
}

Quaternion Quaternion::operator+(const Quaternion &other) const
{
    return Quaternion{x + other.x, y + other.y, z + other.z, w + other.w};
}

Quaternion Quaternion::operator*(const Quaternion &other) const
{
    const double newX = w * other.x + x * other.w + y * other.z - z * other.y;
    const double newY = w * other.y - x * other.z + y * other.w + z * other.x;
    const double newZ = w * other.z + x * other.y - y * other.x + z * other.w;
    const double newW = w * other.w - x * other.x - y * other.y - z * other.z;

    return Quaternion{newX, newY, newZ, newW};
}

Quaternion Quaternion::operator*(double scalar) const
{
    return Quaternion{x * scalar, y * scalar, z * scalar, w * scalar};
}

Quaternion Quaternion::differenceTo(const Quaternion &target) const
{
    return (target * (*this).inverse()).normalized();
}

Quaternion Quaternion::nlerpTo(const Quaternion &target, double t) const
{
    assert(t >= 0 && t <= 1);
    const Quaternion normalizedQuat = normalized();
    const Quaternion normalizedTarget = target.normalized();
    Quaternion adjustedTarget = normalizedTarget;

    if (normalizedQuat.dot(normalizedTarget) < 0)
    {
        adjustedTarget = -normalizedTarget;
    }

    return (normalizedQuat * (1 - t) + adjustedTarget * t).normalized();
}

Quaternion Quaternion::slerpTo(const Quaternion &target, double t) const
{
    assert(t >= 0 && t <= 1);
    const Quaternion normalizedQuat = normalized();
    const Quaternion normalizedTarget = target.normalized();
    Quaternion adjustedTarget = normalizedTarget;

    double cosTheta = normalizedQuat.dot(normalizedTarget);
    if (cosTheta < 0)
    {
        adjustedTarget = -normalizedTarget;
        cosTheta = -cosTheta;
    }
    cosTheta = std::clamp(cosTheta, -1.0, 1.0);
    if (cosTheta > 0.9995)
    {
        return nlerpTo(target, t);
    }
    else
    {
        const double theta = std::acos(cosTheta);
        const double sinTheta = std::sin(theta);
        const double startWeight = std::sin((1 - t) * theta) / sinTheta;
        const double targetWeight = std::sin(t * theta) / sinTheta;

        return (normalizedQuat * startWeight + adjustedTarget * targetWeight).normalized();
    }
}

bool Quaternion::approximatelyEquals(const Quaternion &other, double epsilon) const
{
    assert(epsilon >= 0.0);
    return std::abs(x - other.x) <= epsilon && std::abs(y - other.y) <= epsilon && std::abs(z - other.z) <= epsilon && std::abs(w - other.w) <= epsilon;
}
