#include <engine/math/Quaternion.hpp>

#include <cassert>
#include <cmath>

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
    testLength();
    testNormalization();
    testConjugated();
    testInverse();
    testApproximateEquality();
    return 0;
}