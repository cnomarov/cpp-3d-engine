#pragma once

struct Quaternion
{
    double x;
    double y;
    double z;
    double w;

    static Quaternion identity();
    double length() const;
    Quaternion normalized() const;
    Quaternion conjugated() const;
    Quaternion inverse() const;
    bool approximatelyEquals(const Quaternion &other, double epsilon) const;
};
