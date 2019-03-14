// Interface for 2D points
#ifndef CONVEXPOLYGON_POINT_H
#define CONVEXPOLYGON_POINT_H

#include <iostream>
#include "Vector2D.h"

using namespace std;


// 2D Point representation
struct Point {
    double x, y;
};

// Vector difference between points
Vector2D operator-(const Point &A, const Point &B);

// Equality comparison between points
bool operator==(const Point &A, const Point &B);
bool operator!=(const Point &A, const Point &B);

// Euclidean distance between A and B
double distance(const Point &A, const Point &B);

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

// Returns whether the vector AC lies clockwise with respect to AB
bool isClockwiseTurn(const Point &A, const Point &B, const Point &C);

// Reads space-separated x, y coordinates into P
istream &operator>>(istream &is, Point &P);

// Formats P into space-separated x, y coordinates with 3-digit precision
ostream &operator<<(ostream &os, const Point &P);


#endif
