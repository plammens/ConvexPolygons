// Geometric utilities

#ifndef CONVEXPOLYGONS_GEOM_H
#define CONVEXPOLYGONS_GEOM_H

#include "class/Point.h"
#include "details/range.h"


// Represents a segment delimited by two points
struct Segment {
    Point startPt, endPt;

    Vector2D direction() const;
};


struct IntersectResult {
    Point point;
    bool success;

    explicit
    operator bool() const { return success; };
};


IntersectResult intersect(const Segment &seg1, const Segment &seg2);

bool isInSegment(const Point &P, const Segment &r);


// Returns whether the vector AC lies clockwise with respect to AB
bool isClockwiseTurn(const Point &A, const Point &B, const Point &C);
bool isCounterClockwiseTurn(const Point &A, const Point &B, const Point &C);

// Barycenter of a range of points
Point barycenter(ConstRange <Point> points);

namespace PointComp {
    bool xCoord(const Point &A, const Point &B);

    struct yAngle {
        Point origin;
        bool reversed;

        explicit
        yAngle(const Point &P, bool descending = false);
        bool operator()(const Point &A, const Point &B);
    };
}


#endif //CONVEXPOLYGONS_GEOM_H
