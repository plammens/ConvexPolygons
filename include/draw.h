#ifndef CONVEXPOLYGONS_DRAW_H
#define CONVEXPOLYGONS_DRAW_H

#include <vector>
#include <pngwriter.h>

#include "consts.h"
#include "class/Point.h"
#include "class/ConvexPolygon.h"


using namespace std;

// TODO: single point polygons / empty polygon handling
// TODO: center image


// draws png with polygons
void draw(const string &file, const Range<ConvexPolygon> polygons);

class ScaleHelper {
    double minCoord, totalLength;

public:
    ScaleHelper(const Range<ConvexPolygon> polygons);
    int operator()(double coord) const;
};

void plotPolygon(pngwriter &png, const ConvexPolygon &pol, const ScaleHelper &scale);


#endif //CONVEXPOLYGONS_DRAW_H
