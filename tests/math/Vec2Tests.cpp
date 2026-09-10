#include <engine/math/Vec2.hpp>

#include <cassert>
#include <cmath>

constexpr double testEpsilon = 0.000000001;

void assertApproximatelyEqual(double actual, double expected, double epsilon)
{
    assert(std::abs(actual - expected) <= epsilon);
}

void testAddition()
{
    const Vec2 left{3.0, 4.0};
    const Vec2 right{4.0, 5.0};

    const Vec2 actual = left + right;
    const Vec2 expected{7.0, 9.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testSubtraction()
{
    const Vec2 left{4.0, 5.0};
    const Vec2 right{3.0, 4.0};

    const Vec2 actual = left - right;
    const Vec2 expected{1.0, 1.0};
    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testScalarMultiplication()
{
    const double scalar = 2.0;
    const Vec2 vector{4.0, 5.0};

    const Vec2 actual = vector * scalar;
    const Vec2 expected{8.0, 10.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testLength()
{
    const Vec2 vector{3.0, 4.0};

    const double actual = vector.length();
    const double expected = 5.0;

    assertApproximatelyEqual(actual, expected, testEpsilon);
}

void testNormalization()
{
    const Vec2 vector{3.0, 4.0};

    const Vec2 actual = vector.normalized();
    const Vec2 expected{0.6, 0.8};

    assert(actual.approximatelyEquals(expected, testEpsilon));
    assertApproximatelyEqual(actual.length(), 1.0, testEpsilon);
}

void testZeroVectorNormalization()
{
    const Vec2 zeroVector{0.0, 0.0};

    const Vec2 actual = zeroVector.normalized();
    const Vec2 expected{0.0, 0.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testDotProduct()
{
    const Vec2 right{1.0, 0.0};
    const Vec2 up{0.0, 1.0};
    const Vec2 left{-1.0, 0.0};

    const double expectedPerpendicular = 0.0;
    const double expectedSameDirection = 1.0;
    const double expectedOppositeDirection = -1.0;

    assertApproximatelyEqual(right.dot(up), expectedPerpendicular, testEpsilon);
    assertApproximatelyEqual(right.dot(right), expectedSameDirection, testEpsilon);
    assertApproximatelyEqual(right.dot(left), expectedOppositeDirection, testEpsilon);
}

void testDistance()
{
    const Vec2 left{1.0, 2.0};
    const Vec2 right{4.0, 6.0};

    const double actual = left.distanceTo(right);
    const double expected = 5.0;

    assertApproximatelyEqual(actual, expected, testEpsilon);
    assertApproximatelyEqual(actual, right.distanceTo(left), testEpsilon);
}

void testProjection()
{
    const Vec2 vector{3.0, 4.0};
    const Vec2 axis{2.0, 0.0};

    const Vec2 actual = vector.projectedOnto(axis);
    const Vec2 expected{3.0, 0.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testScalarDivision()
{
    const Vec2 vector{8.0, 10.0};
    const double scalar = 2.0;

    const Vec2 actual = vector / scalar;
    const Vec2 expected{4.0, 5.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testUnaryMinus()
{
    const Vec2 vector{3.0, -4.0};

    const Vec2 actual = -vector;
    const Vec2 expected{-3.0, 4.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testApproximateEquality()
{
    const Vec2 vector{3.0, 4.0};
    const Vec2 close{vector.x + testEpsilon / 2.0, vector.y + testEpsilon / 2.0};
    const Vec2 far{vector.x + testEpsilon * 2.0, vector.y + testEpsilon * 2.0};

    assert(vector.approximatelyEquals(close, testEpsilon));
    assert(!vector.approximatelyEquals(far, testEpsilon));
}

int main()
{
    testAddition();
    testSubtraction();
    testScalarMultiplication();
    testLength();
    testNormalization();
    testZeroVectorNormalization();
    testDotProduct();
    testDistance();
    testProjection();
    testScalarDivision();
    testUnaryMinus();
    testApproximateEquality();
    return 0;
}
