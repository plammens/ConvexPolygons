// Geometric utilities

#ifndef CONVEXPOLYGONS_GEOM_H
#define CONVEXPOLYGONS_GEOM_H

#include "class/Point.h"


// Represents a segment as a line Ax + By = C delimited by two points
class Segment {
    Point _start, _end;
    double _A, _B, _C;

public:
    Segment(const Point &, const Point &);
    double A() const { return _A; }
    double B() const { return _B; }
    double C() const { return _C; }
    const Point &start() const { return _start; }
    const Point &end() const { return _end; }
};


struct IntersectResult {
    Point point;
    bool success;
};


IntersectResult intersect(const Segment &r, const Segment &s);

bool isInSegment(const Point &P, const Segment &r);


#endif //CONVEXPOLYGONS_GEOM_H
