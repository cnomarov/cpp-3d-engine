#include <engine/math/Mat4.hpp>

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

void assertMat4Equals(const Mat4 &actual, const Mat4 &expected)
{
    assert(actual.m00 == expected.m00);
    assert(actual.m01 == expected.m01);
    assert(actual.m02 == expected.m02);
    assert(actual.m03 == expected.m03);
    assert(actual.m10 == expected.m10);
    assert(actual.m11 == expected.m11);
    assert(actual.m12 == expected.m12);
    assert(actual.m13 == expected.m13);
    assert(actual.m20 == expected.m20);
    assert(actual.m21 == expected.m21);
    assert(actual.m22 == expected.m22);
    assert(actual.m23 == expected.m23);
    assert(actual.m30 == expected.m30);
    assert(actual.m31 == expected.m31);
    assert(actual.m32 == expected.m32);
    assert(actual.m33 == expected.m33);
}

void testIdentity()
{
    const Mat4 actual = Mat4::identity();
    // clang-format off
    const Mat4 expected{
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
    };
    // clang-format on

    assertMat4Equals(actual, expected);
}

void testScaling()
{
    const Vec3 scale{2.0, 0.5, -1.0};
    const Vec4 point{2.0, 3.0, 4.0, 1.0};

    const Vec4 actual = Mat4::scaling(scale) * point;
    const Vec4 expected{4.0, 1.5, -4.0, 1.0};

    assertVec4ApproximatelyEquals(actual, expected);
}

void testRotationX()
{
    const Mat4 rotation = Mat4::rotationX(std::numbers::pi / 2.0);
    const Vec4 up{0.0, 1.0, 0.0, 1.0};

    const Vec4 actual = rotation * up;
    const Vec4 expected{0.0, 0.0, 1.0, 1.0};

    assertVec4ApproximatelyEquals(actual, expected);
}

void testRotationY()
{
    const Mat4 rotation = Mat4::rotationY(std::numbers::pi / 2.0);
    const Vec4 forward{0.0, 0.0, 1.0, 1.0};

    const Vec4 actual = rotation * forward;
    const Vec4 expected{1.0, 0.0, 0.0, 1.0};

    assertVec4ApproximatelyEquals(actual, expected);
}

void testRotationZ()
{
    const Mat4 rotation = Mat4::rotationZ(std::numbers::pi / 2.0);
    const Vec4 right{1.0, 0.0, 0.0, 1.0};

    const Vec4 actual = rotation * right;
    const Vec4 expected{0.0, 1.0, 0.0, 1.0};

    assertVec4ApproximatelyEquals(actual, expected);
}

void testTranslation()
{
    const Vec3 offset{2.0, 3.0, 4.0};
    const Mat4 actual = Mat4::translation(offset);
    // clang-format off
    const Mat4 expected{
        1.0, 0.0, 0.0, 2.0,
        0.0, 1.0, 0.0, 3.0,
        0.0, 0.0, 1.0, 4.0,
        0.0, 0.0, 0.0, 1.0,
    };
    // clang-format on

    assertMat4Equals(actual, expected);

    const Vec4 point{1.0, 1.0, 1.0, 1.0};
    const Vec4 direction{1.0, 1.0, 1.0, 0.0};
    const Vec4 expectedPoint{3.0, 4.0, 5.0, 1.0};

    assertVec4ApproximatelyEquals(actual * point, expectedPoint);
    assertVec4ApproximatelyEquals(actual * direction, direction);
}

void testVectorMultiplication()
{
    // clang-format off
    const Mat4 matrix{
        1.0,  2.0,  3.0,  4.0,
        5.0,  6.0,  7.0,  8.0,
        9.0, 10.0, 11.0, 12.0,
       13.0, 14.0, 15.0, 16.0,
    };
    // clang-format on
    const Vec4 vector{1.0, 2.0, 3.0, 4.0};

    const Vec4 actual = matrix * vector;
    const Vec4 expected{30.0, 70.0, 110.0, 150.0};

    assertVec4ApproximatelyEquals(actual, expected);
}

void testMatrixMultiplication()
{
    // clang-format off
    const Mat4 left{
        1.0,  2.0,  3.0,  4.0,
        5.0,  6.0,  7.0,  8.0,
        9.0, 10.0, 11.0, 12.0,
       13.0, 14.0, 15.0, 16.0,
    };
    const Mat4 right{
       16.0, 15.0, 14.0, 13.0,
       12.0, 11.0, 10.0,  9.0,
        8.0,  7.0,  6.0,  5.0,
        4.0,  3.0,  2.0,  1.0,
    };
    const Mat4 expected{
        80.0,  70.0,  60.0,  50.0,
       240.0, 214.0, 188.0, 162.0,
       400.0, 358.0, 316.0, 274.0,
       560.0, 502.0, 444.0, 386.0,
    };
    // clang-format on

    const Mat4 actual = left * right;

    assertMat4Equals(actual, expected);
}

void testTransposed()
{
    // clang-format off
    const Mat4 matrix{
        1.0,  2.0,  3.0,  4.0,
        5.0,  6.0,  7.0,  8.0,
        9.0, 10.0, 11.0, 12.0,
       13.0, 14.0, 15.0, 16.0,
    };
    const Mat4 expected{
        1.0, 5.0,  9.0, 13.0,
        2.0, 6.0, 10.0, 14.0,
        3.0, 7.0, 11.0, 15.0,
        4.0, 8.0, 12.0, 16.0,
    };
    // clang-format on

    const Mat4 actual = matrix.transposed();

    assertMat4Equals(actual, expected);
}

void testTransformComposition()
{
    const Mat4 scale = Mat4::scaling({2.0, 1.0, 1.0});
    const Mat4 rotation = Mat4::rotationZ(std::numbers::pi / 2.0);
    const Mat4 translation = Mat4::translation({10.0, 20.0, 30.0});
    const Mat4 transform = translation * rotation * scale;
    const Vec4 point = Vec4::fromPoint({1.0, 0.0, 0.0});

    const Vec4 actual = transform * point;
    const Vec4 expected{10.0, 22.0, 30.0, 1.0};

    assertVec4ApproximatelyEquals(actual, expected);
}

int main()
{
    testIdentity();
    testScaling();
    testRotationX();
    testRotationY();
    testRotationZ();
    testTranslation();
    testVectorMultiplication();
    testMatrixMultiplication();
    testTransposed();
    testTransformComposition();
    return 0;
}
