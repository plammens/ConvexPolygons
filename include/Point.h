// Interface for 2D points

#ifndef CONVEXPOLYGON_POINT_H
#define CONVEXPOLYGON_POINT_H

#include "Vector2D.h"

// 2D Point representation
struct Point {
    double x, y;
};

// Vector difference between points
Vector2D operator-(const Point &A, const Point &B);

// Equality comparison between points
bool operator==(const Point &A, const Point &B);
bool operator!=(const Point &A, const Point &B);

// Point comparison functions
namespace PointComp {
    bool yCoord(const Point &A, const Point &B);

    struct xAngle {
        Point origin;
        bool reversed;

        xAngle(const Point &P, bool reversed = false);
        bool operator()(const Point &A, const Point &B);
    };
}


bool isClockwiseTurn(const Point &A, const Point &B, const Point &C);


#endif //CONVEXPOLYGON_POINT_H
