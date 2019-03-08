// Interface for 2D points

#ifndef CONVEXPOLYGON_POINT_H
#define CONVEXPOLYGON_POINT_H

#include "Vector2D.h"

// Interface for 2D Points
class Point {
private:
    double _x, _y;

public:
    Point(double x, double y);

    inline double x() const;
    inline double y() const;

    Vector2D operator-(const Point &other) const;
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
