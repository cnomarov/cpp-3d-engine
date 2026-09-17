#include <engine/math/Vec3.hpp>

#include <cassert>
#include <cmath>

constexpr double testEpsilon = 0.000000001;

void assertApproximatelyEqual(double actual, double expected, double epsilon)
{
    assert(std::abs(actual - expected) <= epsilon);
}

void testAddition()
{
    const Vec3 left{1.0, 2.0, 3.0};
    const Vec3 right{4.0, -1.0, 2.0};

    const Vec3 actual = left + right;
    const Vec3 expected{5.0, 1.0, 5.0};

    assert(actual.x == expected.x);
    assert(actual.y == expected.y);
    assert(actual.z == expected.z);
}

void testSubtraction()
{
    const Vec3 left{4.0, 6.0, 3.0};
    const Vec3 right{1.0, 2.0, 3.0};

    const Vec3 actual = left - right;
    const Vec3 expected{3.0, 4.0, 0.0};

    assert(actual.x == expected.x);
    assert(actual.y == expected.y);
    assert(actual.z == expected.z);
}

void testScalarMultiplication()
{
    const double scalar = 2.0;
    const Vec3 vector{2.0, 4.0, 5.0};

    const Vec3 actual = vector * scalar;
    const Vec3 expected{4.0, 8.0, 10.0};

    assert(actual.x == expected.x);
    assert(actual.y == expected.y);
    assert(actual.z == expected.z);
}

void testScalarDivision()
{
    const double scalar = 2.0;
    const Vec3 vector{2.0, 4.0, 6.0};

    const Vec3 actual = vector / scalar;
    const Vec3 expected{1.0, 2.0, 3.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testUnaryMinus()
{
    const Vec3 vector{2.0, 4.0, 6.0};

    const Vec3 actual = -vector;
    const Vec3 expected{-2.0, -4.0, -6.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testLength()
{
    const Vec3 vector{0.0, 3.0, 4.0};

    const double actual = vector.length();
    const double expected = 5.0;

    assertApproximatelyEqual(actual, expected, testEpsilon);
}

void testNormalization()
{
    const Vec3 vector{0.0, 3.0, 4.0};

    const Vec3 actual = vector.normalized();
    const Vec3 expected{0.0, 0.6, 0.8};

    assert(actual.approximatelyEquals(expected, testEpsilon));
    assertApproximatelyEqual(actual.length(), 1.0, testEpsilon);
}

void testZeroVectorNormalization()
{
    const Vec3 zeroVector{0.0, 0.0, 0.0};

    const Vec3 actual = zeroVector.normalized();
    const Vec3 expected{0.0, 0.0, 0.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
}

void testApproximateEquality()
{
    const Vec3 vector{0.0, 3.0, 4.0};
    const Vec3 close{vector.x + testEpsilon / 2.0, vector.y + testEpsilon / 2.0, vector.z + testEpsilon / 2.0};
    const Vec3 far{vector.x + testEpsilon * 2.0, vector.y + testEpsilon * 2.0, vector.z + testEpsilon * 2.0};

    assert(vector.approximatelyEquals(close, testEpsilon));
    assert(!vector.approximatelyEquals(far, testEpsilon));
}

void testDotProduct()
{
    const Vec3 right{1.0, 0.0, 0.0};
    const Vec3 up{0.0, 1.0, 0.0};
    const Vec3 left{-1.0, 0.0, 0.0};
    const Vec3 forward{0.0, 0.0, 1.0};
    const Vec3 generalLeft{1.0, 2.0, 3.0};
    const Vec3 generalRight{4.0, -5.0, 6.0};

    const double expectedPerpendicular = 0.0;
    const double expectedSameDirection = 1.0;
    const double expectedOppositeDirection = -1.0;
    const double expectedGeneralDotProduct = 12.0;

    assertApproximatelyEqual(right.dot(up), expectedPerpendicular, testEpsilon);
    assertApproximatelyEqual(right.dot(forward), expectedPerpendicular, testEpsilon);
    assertApproximatelyEqual(right.dot(right), expectedSameDirection, testEpsilon);
    assertApproximatelyEqual(right.dot(left), expectedOppositeDirection, testEpsilon);
    assertApproximatelyEqual(generalLeft.dot(generalRight), expectedGeneralDotProduct, testEpsilon);
}

void testCrossProduct()
{
    const Vec3 right{1.0, 0.0, 0.0};
    const Vec3 up{0.0, 1.0, 0.0};

    const Vec3 actual = right.cross(up);
    const Vec3 expected{0.0, 0.0, 1.0};

    assert(actual.approximatelyEquals(expected, testEpsilon));
    assert(up.cross(right).approximatelyEquals(-expected, testEpsilon));
}

void testDistance()
{
    const Vec3 left{0.0, 1.0, 2.0};
    const Vec3 right{0.0, 4.0, 6.0};

    const double actual = left.distanceTo(right);
    const double expected = 5.0;

    assertApproximatelyEqual(actual, expected, testEpsilon);
    assertApproximatelyEqual(actual, right.distanceTo(left), testEpsilon);
}

int main()
{
    testAddition();
    testSubtraction();
    testScalarMultiplication();
    testScalarDivision();
    testUnaryMinus();
    testLength();
    testNormalization();
    testZeroVectorNormalization();
    testApproximateEquality();
    testDotProduct();
    testCrossProduct();
    testDistance();
    return 0;
}
