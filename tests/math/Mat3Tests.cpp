#include <engine/math/Mat3.hpp>

#include <cassert>
#include <numbers>

constexpr double testEpsilon = 0.000000001;

void assertVec3ApproximatelyEquals(const Vec3 &actual, const Vec3 &expected)
{
    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void assertMat3Equals(const Mat3 &actual, const Mat3 &expected)
{
    assert(actual.m00 == expected.m00);
    assert(actual.m01 == expected.m01);
    assert(actual.m02 == expected.m02);
    assert(actual.m10 == expected.m10);
    assert(actual.m11 == expected.m11);
    assert(actual.m12 == expected.m12);
    assert(actual.m20 == expected.m20);
    assert(actual.m21 == expected.m21);
    assert(actual.m22 == expected.m22);
}

void testIdentity()
{
    const Mat3 actual = Mat3::identity();
    // clang-format off
    const Mat3 expected{
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
    };
    // clang-format on

    assertMat3Equals(actual, expected);
}

void testScaling()
{
    const Vec3 vector{2.0, 3.0, 1.0};
    const Vec3 testVector{4.0, 2.0, 3.0};
    const Mat3 scalingMat = Mat3::scaling(vector);

    const Vec3 actual = scalingMat * testVector;
    const Vec3 expected{8.0, 6.0, 3.0};

    assertVec3ApproximatelyEquals(actual, expected);
}

void testRotationZ()
{
    const double radians = std::numbers::pi / 2;
    const Vec3 vector{1.0, 0.0, 0.0};

    const Mat3 rotationZMatrix = Mat3::rotationZ(radians);
    const Vec3 actual = rotationZMatrix * vector;
    const Vec3 expected{0.0, 1.0, 0.0};

    assertVec3ApproximatelyEquals(actual, expected);
}

void testRotationX()
{
    const double radians = std::numbers::pi / 2;
    const Vec3 vector{0.0, 1.0, 0.0};

    const Mat3 rotationXMatrix = Mat3::rotationX(radians);
    const Vec3 actual = rotationXMatrix * vector;
    const Vec3 expected{0.0, 0.0, 1.0};

    assertVec3ApproximatelyEquals(actual, expected);
}

void testRotationY()
{
    const double radians = std::numbers::pi / 2;
    const Vec3 vector{0.0, 0.0, 1.0};

    const Mat3 rotationYMatrix = Mat3::rotationY(radians);
    const Vec3 actual = rotationYMatrix * vector;
    const Vec3 expected{1.0, 0.0, 0.0};

    assertVec3ApproximatelyEquals(actual, expected);
}

void testMultiply()
{
    // clang-format off
    const Mat3 mat{
        1.0, 2.0, 3.0,
        0.0, -1.0, 4.0,
        2.0, 0.0, 1.0
    };
    // clang-format on
    const Vec3 vector{2.0, 3.0, 1.0};

    const Vec3 actual = mat * vector;
    const Vec3 expected{11.0, 1.0, 5.0};

    assertVec3ApproximatelyEquals(actual, expected);
}

void testMultiplyWithIdentity()
{
    const Mat3 identityMat = Mat3::identity();
    const Vec3 vector{2.0, 3.0, 4.0};

    const Vec3 actual = identityMat * vector;
    const Vec3 expected{2.0, 3.0, 4.0};

    assertVec3ApproximatelyEquals(actual, expected);
}

void testMatrixMultiplication()
{
    // clang-format off
    const Mat3 matA{
        1.0, 2.0, 3.0,
        0.0, -1.0, 4.0,
        2.0, 0.0, 1.0
    };

    const Mat3 matB{
        2.0, 0.0, 1.0,
        1.0, 3.0, 0.0,
        0.0, 2.0, -1.0
    };
    // clang-format on

    const Mat3 actual = matA * matB;
    // clang-format off
    const Mat3 expected{
        4.0, 12.0, -2.0,
        -1.0, 5.0, -4.0,
        4.0, 2.0, 1.0
    };
    // clang-format on
    assertMat3Equals(actual, expected);
}

void testTransposed()
{
    // clang-format off
    const Mat3 mat{
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };
    // clang-format on

    const Mat3 actual = mat.transposed();
    // clang-format off
    const Mat3 expected{
        1.0, 4.0, 7.0,
        2.0, 5.0, 8.0,
        3.0, 6.0, 9.0
    };
    // clang-format on

    assertMat3Equals(actual, expected);
}

int main()
{
    testIdentity();
    testScaling();
    testRotationZ();
    testRotationX();
    testRotationY();
    testMultiply();
    testMultiplyWithIdentity();
    testMatrixMultiplication();
    testTransposed();
    return 0;
}
