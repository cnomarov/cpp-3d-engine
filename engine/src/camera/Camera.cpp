#include <engine/camera/Camera.hpp>

Mat4 Camera::viewMatrix() const
{
    return Mat4::rotationX(-pitchRadians) * Mat4::rotationY(-yawRadians) * Mat4::translation(-position);
}

Mat4 Camera::projectionMatrix(double aspectRatio) const
{
    return Mat4::perspective(verticalFovRadians, aspectRatio, nearPlane, farPlane);
}