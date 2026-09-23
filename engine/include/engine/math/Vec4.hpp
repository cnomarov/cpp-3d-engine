#pragma once

#include <engine/math/Vec3.hpp>

struct Vec4
{
    double x;
    double y;
    double z;
    double w;

    static Vec4 fromPoint(const Vec3 &value);
    static Vec4 fromDirection(const Vec3 &value);
};