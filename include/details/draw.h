// Utilities for drawing polygons to PNGs

#ifndef CONVEXPOLYGONS_DRAW_H
#define CONVEXPOLYGONS_DRAW_H

#include <vector>
#include <pngwriter.h>
#include "class/Point.h"
#include "class/ConvexPolygon.h"
#include "range.h"


// draws png with polygons
void draw(const std::string &file, ConstRange<ConvexPolygon> polygons, bool fill = false);


// Utility to map points to their pixel-coordinates
class ScaleHelper {
    double minX, minY, maxLength;
    int xOffset, yOffset;

public:
    ScaleHelper(ConstRange<ConvexPolygon> polygons);
    std::pair<int, int> operator()(const Point &P) const;
    int scaleX(double x) const;
    int scaleY(double y) const;
};


// Draws and fills a polygon
void drawPolygon(pngwriter &png, const ConvexPolygon &pol, const ScaleHelper &scale, bool fill);


#endif //CONVEXPOLYGONS_DRAW_H
