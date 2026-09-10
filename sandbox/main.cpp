#include <iostream>

#include <engine/math/Vec2.hpp>

#include <cmath>

double calculateArea(double width, double height)
{
    return width * height;
}

double calculatePerimeter(double width, double height)
{
    return 2 * (width + height);
}

int main()
{
    double width = 0.0;
    double height = 0.0;
    const Vec2 firstVector{3.0, 4.0};
    const Vec2 secondVector{4.0, 5.0};
    const Vec2 right{1.0, 0.0};
    const Vec2 up{0.0, 1.0};
    const Vec2 left{-1.0, 0.0};
    const Vec2 pointA{1.0, 2.0};
    const Vec2 pointB{4.0, 6.0};
    const double epsilon = 0.000000001;
    const double floatingPointSum = 0.1 + 0.2;
    const double absoluteDifference = std::abs(floatingPointSum - 0.3);
    const bool approximateEquality = absoluteDifference <= epsilon;
    const bool exactEquality = floatingPointSum == 0.3;
    const Vec2 first{0.1 + 0.2, 0.3};
    const Vec2 second{0.3, 0.3};

    std::cout << "Enter width: ";
    std::cin >> width;
    std::cout << "Enter height: ";
    std::cin >> height;

    const double perimeter = calculatePerimeter(width, height);
    const double area = calculateArea(width, height);
    const Vec2 summedVector = firstVector + secondVector;
    const Vec2 differenceVector = firstVector - secondVector;
    const double firstVectorLength = firstVector.length();
    const Vec2 normalizedFirstVector = firstVector.normalized();
    const double normalizedFirstVectorLength = normalizedFirstVector.length();
    const double dotProduct = firstVector.dot(secondVector);
    const double axesDotProduct = right.dot(up);
    const double oppositeDotProduct = right.dot(left);
    const Vec2 multipliedVector = firstVector * 2.0;
    const Vec2 dividedVector = firstVector / 2.0;
    const Vec2 oppositeVector = -firstVector;
    const Vec2 firstVectorProjectedOntoRight = firstVector.projectedOnto(right);
    const Vec2 firstVectorProjectedOntoUp = firstVector.projectedOnto(up);

    std::cout << "Area: " << area << '\n';
    std::cout << "Perimeter: " << perimeter << '\n';
    std::cout << "First vector: (" << firstVector.x << ", " << firstVector.y << ")" << '\n';
    std::cout << "First vector length: " << firstVectorLength << '\n';

    std::cout << "Sum: (" << summedVector.x << ", " << summedVector.y << ")" << '\n';
    std::cout << "Difference: (" << differenceVector.x << ", " << differenceVector.y << ")" << '\n';

    std::cout << "Multiplication: (" << multipliedVector.x << ", " << multipliedVector.y << ")" << '\n';
    std::cout << "Multiplied vector length: " << multipliedVector.length() << '\n';

    std::cout << "Divided Vector: (" << dividedVector.x << ", " << dividedVector.y << ")" << '\n';
    std::cout << "Divided vector length: " << dividedVector.length() << '\n';

    std::cout << "Opposite Vector: (" << oppositeVector.x << ", " << oppositeVector.y << ")" << '\n';
    std::cout << "Opposite vector length: " << oppositeVector.length() << '\n';

    std::cout << "Normalized first vector: (" << normalizedFirstVector.x << ", " << normalizedFirstVector.y << ")" << '\n';
    std::cout << "Normalized first vector length: " << normalizedFirstVectorLength << '\n';

    std::cout << "Distance between points A and B: " << pointA.distanceTo(pointB) << '\n';

    std::cout << "First vector projected onto vector Right: (" << firstVectorProjectedOntoRight.x << ", " << firstVectorProjectedOntoRight.y << ")" << '\n';
    std::cout << "First vector projected onto vector Up: (" << firstVectorProjectedOntoUp.x << ", " << firstVectorProjectedOntoUp.y << ")" << '\n';

    std::cout << "Dot first and second vector: " << dotProduct << '\n';
    std::cout << "Axes Dot product: " << axesDotProduct << '\n';
    std::cout << "Opposite axes Dot product: " << oppositeDotProduct << '\n';

    std::cout << std::boolalpha << "Exact equality: " << exactEquality << '\n';
    std::cout << "Approximate equality: " << approximateEquality << '\n';
    std::cout << "First vector approximately equals second? " << first.approximatelyEquals(second, epsilon) << '\n';

    return 0;
}
