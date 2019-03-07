//
// Created by Paolo on 07/03/2019.
//

#include "../include/Point.h"

// Constructs a Point with the given (x, y) coordinates
Point::Point(double x, double y) : x(x), y(y) {}

// Strict weak Point comparison by y-coordinate.
// Returns whether A has a smaller y-coordinate than B
// (and smaller x-coordinate in case of equality).
bool Point::yComp(const Point &A, const Point &B) {
    if (A.y != B.y) return A.y < B.y;
    return A.x < B.x;
}
