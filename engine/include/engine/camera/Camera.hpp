#pragma once

#include <engine/math/Vec3.hpp>
#include <engine/math/Mat4.hpp>

class Camera
{
public:
    Vec3 position;
    double yawRadians;
    double pitchRadians;
    double verticalFovRadians;
    double nearPlane;
    double farPlane;

    Mat4 viewMatrix() const;
    Mat4 projectionMatrix(double aspectRatio) const;
};
