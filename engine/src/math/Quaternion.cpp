#include <engine/math/Quaternion.hpp>

#include <cassert>
#include <cmath>

Quaternion Quaternion::identity()
{
    return Quaternion{0.0, 0.0, 0.0, 1.0};
}

double Quaternion::length() const
{
    return std::sqrt(x * x + y * y + z * z + w * w);
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

bool Quaternion::approximatelyEquals(const Quaternion &other, double epsilon) const
{
    assert(epsilon >= 0.0);
    return std::abs(x - other.x) <= epsilon && std::abs(y - other.y) <= epsilon && std::abs(z - other.z) <= epsilon && std::abs(w - other.w) <= epsilon;
}
