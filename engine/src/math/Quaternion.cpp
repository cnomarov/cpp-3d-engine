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

double Quaternion::length() const
{
    return std::sqrt(x * x + y * y + z * z + w * w);
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

Quaternion Quaternion::operator*(const Quaternion &other) const
{
    const double newX = w * other.x + x * other.w + y * other.z - z * other.y;
    const double newY = w * other.y - x * other.z + y * other.w + z * other.x;
    const double newZ = w * other.z + x * other.y - y * other.x + z * other.w;
    const double newW = w * other.w - x * other.x - y * other.y - z * other.z;

    return Quaternion{newX, newY, newZ, newW};
}

bool Quaternion::approximatelyEquals(const Quaternion &other, double epsilon) const
{
    assert(epsilon >= 0.0);
    return std::abs(x - other.x) <= epsilon && std::abs(y - other.y) <= epsilon && std::abs(z - other.z) <= epsilon && std::abs(w - other.w) <= epsilon;
}
