#ifndef CONVEXPOLYGONS_DRAW_H
#define CONVEXPOLYGONS_DRAW_H

#include <vector>
#include "consts.h"
#include "class/Point.h"


using namespace std;


// draws png with polygons
void draw(const string &file, const vector<string> &polygonIDs, const PolygonMap &polygons);

vector<double> flatten(const Points &points);
#endif //CONVEXPOLYGONS_DRAW_H
