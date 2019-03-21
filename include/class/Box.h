// Box class

#ifndef CONVEXPOLYGONS_BOX_H
#define CONVEXPOLYGONS_BOX_H

#include "Point.h"


// Lightweight representation of a geometric box (e.g. a bounding box)
class Box {
    Point _SW, _NW, _NE, _SE;

public:
    Box(const Point &, const Point &, const Point &, const Point &);


    const Point &SW() const { return _SW; }
    const Point &NW() const { return _NW; }
    const Point &NE() const { return _NE; }
    const Point &SE() const { return _SE; }
};


#endif //CONVEXPOLYGONS_BOX_H
