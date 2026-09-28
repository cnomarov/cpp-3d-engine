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

void testRotatedVector()
{
    const Quaternion rotation = Quaternion::fromAxisAngle({0.0, 0.0, 1.0}, std::numbers::pi / 2.0);
    const Vec3 right{1.0, 0.0, 0.0};

    const Vec3 actual = rotation.rotated(right);
    const Vec3 expected{0.0, 1.0, 0.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testLength()
{
    const Quaternion quaternion{1.0, 2.0, 2.0, 0.0};

    const double actual = quaternion.length();
    const double expected = 3.0;

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
    testRotatedVector();
    testLength();
    testNormalization();
    testConjugated();
    testInverse();
    testApproximateEquality();
    testMultiplication();
    return 0;
}