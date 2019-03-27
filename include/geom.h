// Geometric utilities

#ifndef CONVEXPOLYGONS_GEOM_H
#define CONVEXPOLYGONS_GEOM_H

#include "class/Point.h"


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


#endif //CONVEXPOLYGONS_GEOM_H
