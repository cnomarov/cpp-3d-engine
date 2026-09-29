#include <engine/math/Quaternion.hpp>

#include <cassert>
#include <cmath>
#include <numbers>

constexpr double testEpsilon = 0.000000001;

void assertApproximatelyEqual(double actual, double expected, double epsilon)
{
    assert(std::abs(actual - expected) <= epsilon);
}

void testIdentity()
{
    const Quaternion actual = Quaternion::identity();
    const Quaternion expected{0.0, 0.0, 0.0, 1.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testFromAxisAngle()
{
    const Vec3 axis{0.0, 0.0, 2.0};
    const double radians = std::numbers::pi / 2;
    const Quaternion actual = Quaternion::fromAxisAngle(axis, radians);
    const Quaternion expected{0.0, 0.0, std::sqrt(0.5), std::sqrt(0.5)};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testFromEulerXYZ()
{
    const Vec3 radians{std::numbers::pi / 2, 0.0, std::numbers::pi / 4};
    const Quaternion actual = Quaternion::fromEulerXYZ(radians);

    const double sinPiOverEight = std::sin(std::numbers::pi / 8.0);
    const double cosPiOverEight = std::cos(std::numbers::pi / 8.0);
    const double sqrtHalf = std::sqrt(0.5);

    const Quaternion expected{
        cosPiOverEight * sqrtHalf,
        sinPiOverEight * sqrtHalf,
        sinPiOverEight * sqrtHalf,
        cosPiOverEight * sqrtHalf,
    };

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testToEulerXYZ()
{
    const Vec3 expected{
        std::numbers::pi / 3.0,
        std::numbers::pi / 6.0,
        std::numbers::pi / 4.0,
    };
    const Quaternion quaternion = Quaternion::fromEulerXYZ(expected);

    const Vec3 actual = quaternion.toEulerXYZ();

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testRotatedVector()
{
    const Quaternion rotation = Quaternion::fromAxisAngle({0.0, 0.0, 1.0}, std::numbers::pi / 2.0);
    const Vec3 right{1.0, 0.0, 0.0};

    const Vec3 actual = rotation.rotated(right);
    const Vec3 expected{0.0, 1.0, 0.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testRotationComposition()
{
    const Quaternion rotationX = Quaternion::fromAxisAngle({1.0, 0.0, 0.0}, std::numbers::pi / 2.0);
    const Quaternion rotationZ = Quaternion::fromAxisAngle({0.0, 0.0, 1.0}, std::numbers::pi / 2.0);
    const Vec3 initialVector{1.0, 0.0, 0.0};

    const Quaternion rotationXZ = rotationZ * rotationX;
    const Quaternion rotationZX = rotationX * rotationZ;

    const Vec3 vectorXZ = rotationXZ.rotated(initialVector);
    const Vec3 vectorZX = rotationZX.rotated(initialVector);

    assert(vectorXZ.approximatelyEquals({0.0, 1.0, 0.0}, testEpsilon));
    assert(vectorZX.approximatelyEquals({0.0, 0.0, 1.0}, testEpsilon));
}

void testToMat3()
{
    const Quaternion rotation = Quaternion::fromEulerXYZ({
        std::numbers::pi / 3.0,
        std::numbers::pi / 6.0,
        std::numbers::pi / 4.0,
    });
    const Vec3 vector{1.0, 2.0, 3.0};

    const Vec3 actualA = rotation.rotated(vector);
    const Vec3 actualB = rotation.toMat3() * vector;

    assert(actualA.approximatelyEquals(actualB, testEpsilon));
}

void testFromMat3()
{
    // clang-format off
    const Mat3 matrix{
        0.0, -1.0, 0.0,
        1.0,  0.0, 0.0,
        0.0,  0.0, 1.0,
    };
    // clang-format on
    const Quaternion actual = Quaternion::fromMat3(matrix);
    const Quaternion expected{0.0, 0.0, std::sqrt(0.5), std::sqrt(0.5)};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testFromMat3WithNonPositiveTrace()
{
    // clang-format off
    const Mat3 matrixX{
        1.0,  0.0,  0.0,
        0.0, -1.0,  0.0,
        0.0,  0.0, -1.0
    };
    const Mat3 matrixY{
        -1.0, 0.0,  0.0,
         0.0, 1.0,  0.0,
         0.0, 0.0, -1.0
    };
    const Mat3 matrixZ{
        -1.0,  0.0, 0.0,
         0.0, -1.0, 0.0,
         0.0,  0.0, 1.0
    };
    // clang-format on

    const Quaternion actualX = Quaternion::fromMat3(matrixX);
    const Quaternion actualY = Quaternion::fromMat3(matrixY);
    const Quaternion actualZ = Quaternion::fromMat3(matrixZ);

    const Quaternion expectedX{1.0, 0.0, 0.0, 0.0};
    const Quaternion expectedY{0.0, 1.0, 0.0, 0.0};
    const Quaternion expectedZ{0.0, 0.0, 1.0, 0.0};

    assert(actualX.approximatelyEquals(expectedX, testEpsilon));
    assert(actualY.approximatelyEquals(expectedY, testEpsilon));
    assert(actualZ.approximatelyEquals(expectedZ, testEpsilon));
}

void testLength()
{
    const Quaternion quaternion{1.0, 2.0, 2.0, 0.0};

    const double actual = quaternion.length();
    const double expected = 3.0;

    assertApproximatelyEqual(actual, expected, testEpsilon);
}

void testDot()
{
    const Quaternion quaternionA{0.0, 0.0, 0.0, 1.0};
    const Quaternion quaternionB{0.0, 0.0, std::sqrt(0.5), std::sqrt(0.5)};

    const double actual = quaternionA.dot(quaternionB);
    const double expected = std::sqrt(0.5);

    assertApproximatelyEqual(actual, expected, testEpsilon);
}

void testNormalization()
{
    const Quaternion quaternion{0.0, 0.0, 0.0, 2.0};

    const Quaternion actual = quaternion.normalized();
    const Quaternion expected{0.0, 0.0, 0.0, 1.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
    assertApproximatelyEqual(actual.length(), 1.0, testEpsilon);
}

void testConjugated()
{
    const Quaternion quaternion{1.0, -2.0, 3.0, 4.0};

    const Quaternion actual = quaternion.conjugated();
    const Quaternion expected{-1.0, 2.0, -3.0, 4.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testInverse()
{
    const Quaternion quaternion{1.0, 2.0, 2.0, 0.0};

    const Quaternion actual = quaternion.inverse();
    const Quaternion expected{-1.0 / 9.0, -2.0 / 9.0, -2.0 / 9.0, 0.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testMultiplication()
{
    const Quaternion quaternionA{1.0, 2.0, 3.0, 4.0};
    const Quaternion quaternionB{5.0, 6.0, 7.0, 8.0};

    const Quaternion actual = quaternionA * quaternionB;
    const Quaternion expected{24.0, 48.0, 48.0, -6.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testAddition()
{
    const Quaternion quaternionA{1.0, 2.0, 3.0, 4.0};
    const Quaternion quaternionB{5.0, 6.0, 7.0, 8.0};

    const Quaternion actual = quaternionA + quaternionB;
    const Quaternion expected{6.0, 8.0, 10.0, 12.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testScalarMultiplication()
{
    const Quaternion quaternion{1.0, 2.0, 3.0, 4.0};
    const Quaternion actual = quaternion * 0.5;
    const Quaternion expected{0.5, 1.0, 1.5, 2.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testUnaryMinus()
{
    const Quaternion quaternion = Quaternion::fromAxisAngle({0.0, 0.0, 1.0}, std::numbers::pi / 2.0);
    const Quaternion actual = -quaternion;
    const Quaternion expected{-quaternion.x, -quaternion.y, -quaternion.z, -quaternion.w};
    const Vec3 vector{1.0, 0.0, 0.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
    assert(actual.rotated(vector).approximatelyEquals(quaternion.rotated(vector), testEpsilon));
}

void testDifferenceTo()
{
    const Quaternion current = Quaternion::fromAxisAngle({1.0, 0.0, 0.0}, std::numbers::pi / 2);
    const Quaternion target = Quaternion::fromAxisAngle({0.0, 0.0, 1.0}, std::numbers::pi / 2);
    const Quaternion difference = current.differenceTo(target);
    const Quaternion expected{-0.5, -0.5, 0.5, 0.5};

    assert(difference.approximatelyEquals(expected, testEpsilon));
    assert((difference * current).approximatelyEquals(target, testEpsilon));
}

void testNlerpTo()
{
    const Quaternion start = Quaternion::identity();
    const Quaternion target = Quaternion::fromAxisAngle({0.0, 0.0, 1.0}, std::numbers::pi / 2.0);
    const Quaternion expected = Quaternion::fromAxisAngle({0.0, 0.0, 1.0}, std::numbers::pi / 4.0);

    const Quaternion actual = start.nlerpTo(target, 0.5);
    const Quaternion actualWithOppositeSign = start.nlerpTo(-target, 0.5);

    assert(actual.approximatelyEquals(expected, testEpsilon));
    assert(actualWithOppositeSign.approximatelyEquals(expected, testEpsilon));
    assertApproximatelyEqual(actual.length(), 1.0, testEpsilon);
}

void testSlerpTo()
{
    const Quaternion start = Quaternion::identity();
    const Quaternion target = Quaternion::fromAxisAngle({0.0, 0.0, 1.0}, 2.0 * std::numbers::pi / 3.0);
    const Quaternion expected = Quaternion::fromAxisAngle({0.0, 0.0, 1.0}, std::numbers::pi / 6.0);

    const Quaternion actual = start.slerpTo(target, 0.25);
    const Quaternion actualWithOppositeSign = start.slerpTo(-target, 0.25);

    assert(actual.approximatelyEquals(expected, testEpsilon));
    assert(actualWithOppositeSign.approximatelyEquals(expected, testEpsilon));
    assertApproximatelyEqual(actual.length(), 1.0, testEpsilon);
}

void testApproximateEquality()
{
    const Quaternion quaternion{1.0, 2.0, 3.0, 4.0};
    const Quaternion close{
        quaternion.x + testEpsilon / 2.0,
        quaternion.y + testEpsilon / 2.0,
        quaternion.z + testEpsilon / 2.0,
        quaternion.w + testEpsilon / 2.0,
    };
    const Quaternion far{
        quaternion.x + testEpsilon * 2.0,
        quaternion.y + testEpsilon * 2.0,
        quaternion.z + testEpsilon * 2.0,
        quaternion.w + testEpsilon * 2.0,
    };

    assert(quaternion.approximatelyEquals(close, testEpsilon));
    assert(!quaternion.approximatelyEquals(far, testEpsilon));
}

int main()
{
    testIdentity();
    testFromAxisAngle();
    testFromEulerXYZ();
    testToEulerXYZ();
    testRotatedVector();
    testRotationComposition();
    testToMat3();
    testFromMat3();
    testFromMat3WithNonPositiveTrace();
    testLength();
    testDot();
    testNormalization();
    testConjugated();
    testInverse();
    testApproximateEquality();
    testMultiplication();
    testAddition();
    testScalarMultiplication();
    testUnaryMinus();
    testDifferenceTo();
    testNlerpTo();
    testSlerpTo();
    return 0;
}