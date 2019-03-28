/** @file
 * Interface for 2D Points.
*/

#ifndef CONVEXPOLYGONS_POINT_H
#define CONVEXPOLYGONS_POINT_H

#include <istream>
#include <vector>
#include "class/Vector2D.h"
#include "details/range.h"


//////////// POINT STRUCT ////////////

// 2D Point representation (as aggregate type)
struct Point {
    double x, y;
};



//////////// ASSOCIATED NONMEMBER FUNCTIONS ////////////

// Euclidean distance between A and B
double distance(const Point &A, const Point &B);


//// Arithmetic operators ////

// Vector difference between points
Vector2D operator-(const Point &A, const Point &B);

// Adding a vector to a point (yields another point)
Point operator+(const Point &A, const Vector2D& u);


//// Equality operators ////

bool operator==(const Point &A, const Point &B);
bool operator!=(const Point &A, const Point &B);


//// Text IO ////

// Reads space-separated x, y coordinates into P
std::istream &operator>>(std::istream &is, Point &P);

// Formats P into space-separated x, y coordinates with 3-digit precision
std::ostream &operator<<(std::ostream &os, const Point &P);



//////////// TYPEDEFS ////////////

typedef std::vector<Point> Points;  // alias


#endif
