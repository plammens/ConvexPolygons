// Interface for 2D points

#ifndef CONVEXPOLYGON_POINT_H
#define CONVEXPOLYGON_POINT_H

#include "GeometricVector.h"

// Interface for 2D Points
class Point {
private:
    double _x, _y;

public:
    Point(double x, double y);

    double x() const;
    double y() const;

    GeometricVector operator-(const Point &other) const;
};


// Point comparison functions
namespace PointComp {
    bool yComp(const Point &A, const Point &B);

    struct angleComp {
        Point origin;
        angleComp(const Point &P);
        bool operator()(const Point &A, const Point &B);
    };
}


#endif //CONVEXPOLYGON_POINT_H
