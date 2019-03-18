#ifndef CONVEXPOLYGONS_DRAW_H
#define CONVEXPOLYGONS_DRAW_H

#include <vector>
#include <pngwriter.h>

#include "consts.h"
#include "class/Point.h"
#include "class/ConvexPolygon.h"


using namespace std;


// draws png with polygons
void draw(const string &file, const vector<string> &polygonIDs, const PolygonMap &polygons);

class ScaleHelper {
    double minCoord, totalLength;

public:
    ScaleHelper(const vector<string> &polIDs, const PolygonMap &polygons);

    int operator()(double coord) const;
};

void plotPolygon(pngwriter &png, const ConvexPolygon &pol, const ScaleHelper &scale);


#endif //CONVEXPOLYGONS_DRAW_H
