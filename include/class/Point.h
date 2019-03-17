// Interface for 2D points
#ifndef CONVEXPOLYGONS_POINT_H
#define CONVEXPOLYGONS_POINT_H

#include <iostream>
#include <vector>
#include "class/Vector2D.h"


using namespace std;

// 2D Point representation (as aggregate type)
struct Point {
    double x, y;
};

typedef vector<Point> Points;  // alias


// Vector difference between points
Vector2D operator-(const Point &A, const Point &B);

// Adding a vector to a point (yields another point)
Point operator+(const Point &A, const Vector2D& u);

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

// Barycenter of a vector of points
Point barycenter(const Points &points);  // TODO: should do for any container?

// Reads space-separated x, y coordinates into P
istream &operator>>(istream &is, Point &P);

// Formats P into space-separated x, y coordinates with 3-digit precision
ostream &operator<<(ostream &os, const Point &P);


#endif