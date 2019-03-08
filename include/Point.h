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
    bool yCoord(const Point &A, const Point &B);

    struct xAngle {
        Point origin;
        bool reversed;

        xAngle(const Point &P, bool reversed = false);
        bool operator()(const Point &A, const Point &B);
    };
}


#endif //CONVEXPOLYGON_POINT_H
