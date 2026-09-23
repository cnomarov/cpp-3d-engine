#include <engine/math/Vec4.hpp>

#include <cassert>

void testFromPoint()
{
    const Vec3 vector{2.0, 3.0, 4.0};
    const Vec4 actual = Vec4::fromPoint(vector);
    const Vec4 expected{2.0, 3.0, 4.0, 1.0};

    assert(actual.x == expected.x);
    assert(actual.y == expected.y);
    assert(actual.z == expected.z);
    assert(actual.w == expected.w);
}

void testFromDirection()
{
    const Vec3 vector{2.0, 3.0, 4.0};
    const Vec4 actual = Vec4::fromDirection(vector);
    const Vec4 expected{2.0, 3.0, 4.0, 0.0};

    assert(actual.x == expected.x);
    assert(actual.y == expected.y);
    assert(actual.z == expected.z);
    assert(actual.w == expected.w);
}

int main()
{
    testFromPoint();
    testFromDirection();
    return 0;
}
