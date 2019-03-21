#ifndef CONVEXPOLYGONS_DRAW_H
#define CONVEXPOLYGONS_DRAW_H

#include <vector>
#include <pngwriter.h>

#include "aliases.h"
#include "class/Point.h"
#include "class/ConvexPolygon.h"


using namespace std;


// draws png with polygons
void draw(const string &file, Range<ConvexPolygon> polygons);


// Utility to map points to their pixel-coordinates
class ScaleHelper {
    double minX, minY, maxLength;
    int xOffset, yOffset;

public:
    ScaleHelper(Range<ConvexPolygon> polygons);
    pair<int, int> operator()(const Point &P) const;
    int scaleX(double x) const;
    int scaleY(double y) const;
};


// Draws and fills a polygon
void fillPolygon(pngwriter &png, const ConvexPolygon &pol, const ScaleHelper &scale);


#endif //CONVEXPOLYGONS_DRAW_H
