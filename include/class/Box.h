// Box class

#ifndef CONVEXPOLYGONS_BOX_H
#define CONVEXPOLYGONS_BOX_H

#include "class/Point.h"


// Representation of a 2D horizontal (i.e. non-rotated) box (e.g. a bounding box)
class Box {
    Point _SW, _NW, _NE, _SE;

public:
    Box(const Point &P, const Point &Q);

    const Point &SW() const { return _SW; }
    const Point &NW() const { return _NW; }
    const Point &NE() const { return _NE; }
    const Point &SE() const { return _SE; }
};


Point bottomLeft(const Point &A, const Point &B);
Point upperRight(const Point &A, const Point &B);

bool operator==(const Box &lhs, const Box &rhs);
bool operator!=(const Box &lhs, const Box &rhs);


#endif //CONVEXPOLYGONS_BOX_H
