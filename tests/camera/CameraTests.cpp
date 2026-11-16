#include <engine/camera/Camera.hpp>

#include <cassert>
#include <cmath>
#include <numbers>

constexpr double testEpsilon = 0.000000001;

void assertApproximatelyEqual(double actual, double expected)
{
    assert(std::abs(actual - expected) <= testEpsilon);
}

void assertVec4ApproximatelyEquals(const Vec4 &actual, const Vec4 &expected)
{
    assertApproximatelyEqual(actual.x, expected.x);
    assertApproximatelyEqual(actual.y, expected.y);
    assertApproximatelyEqual(actual.z, expected.z);
    assertApproximatelyEqual(actual.w, expected.w);
}

Camera makeCamera()
{
    return Camera{
        .position = {0.0, 0.0, 0.0},
        .yawRadians = 0.0,
        .pitchRadians = 0.0,
        .verticalFovRadians = std::numbers::pi / 2.0,
        .nearPlane = 1.0,
        .farPlane = 10.0,
    };
}

void testViewMatrixMovesCameraPositionToOrigin()
{
    Camera camera = makeCamera();
    camera.position = {2.0, 3.0, 4.0};

    const Vec4 cameraWorldPosition = Vec4::fromPoint(camera.position);
    const Vec4 actual = camera.viewMatrix() * cameraWorldPosition;
    const Vec4 expected{0.0, 0.0, 0.0, 1.0};

    assertVec4ApproximatelyEquals(actual, expected);
}

void testViewMatrixAppliesInverseYaw()
{
    Camera camera = makeCamera();
    camera.yawRadians = std::numbers::pi / 2.0;

    const Vec4 pointInFrontOfCamera = Vec4::fromPoint({1.0, 0.0, 0.0});
    const Vec4 actual = camera.viewMatrix() * pointInFrontOfCamera;
    const Vec4 expected{0.0, 0.0, 1.0, 1.0};

    assertVec4ApproximatelyEquals(actual, expected);
}

void testViewMatrixAppliesInversePitch()
{
    Camera camera = makeCamera();
    camera.pitchRadians = std::numbers::pi / 2.0;

    const Vec4 pointInFrontOfCamera = Vec4::fromPoint({0.0, -1.0, 0.0});
    const Vec4 actual = camera.viewMatrix() * pointInFrontOfCamera;
    const Vec4 expected{0.0, 0.0, 1.0, 1.0};

    assertVec4ApproximatelyEquals(actual, expected);
}

void testProjectionMatrixUsesCameraDepthPlanes()
{
    const Camera camera = makeCamera();
    const Mat4 projection = camera.projectionMatrix(1.0);

    const Vec4 nearClip = projection * Vec4::fromPoint({0.0, 0.0, camera.nearPlane});
    const Vec4 farClip = projection * Vec4::fromPoint({0.0, 0.0, camera.farPlane});

    assertApproximatelyEqual(nearClip.z / nearClip.w, 0.0);
    assertApproximatelyEqual(farClip.z / farClip.w, 1.0);
}

void testProjectionMatrixUsesFovAndAspectRatio()
{
    const Camera camera = makeCamera();
    const Mat4 projection = camera.projectionMatrix(2.0);

    const Vec4 horizontalEdge = projection * Vec4::fromPoint({2.0, 0.0, 1.0});
    const Vec4 verticalEdge = projection * Vec4::fromPoint({0.0, 1.0, 1.0});

    assertApproximatelyEqual(horizontalEdge.x / horizontalEdge.w, 1.0);
    assertApproximatelyEqual(verticalEdge.y / verticalEdge.w, 1.0);
}

int main()
{
    testViewMatrixMovesCameraPositionToOrigin();
    testViewMatrixAppliesInverseYaw();
    testViewMatrixAppliesInversePitch();
    testProjectionMatrixUsesCameraDepthPlanes();
    testProjectionMatrixUsesFovAndAspectRatio();
    return 0;
}
