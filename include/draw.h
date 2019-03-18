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

void plotPolygon(const ConvexPolygon & pol, pngwriter &png);

// util for converting to vector<int>
vector<int> flattenAndRescale(const Points &points);


#endif //CONVEXPOLYGONS_DRAW_H
