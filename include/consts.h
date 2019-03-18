//

#ifndef CONVEXPOLYGONS_CONSTS_H
#define CONVEXPOLYGONS_CONSTS_H

#include <string>
#include <map>
#include <vector>
#include "class/ConvexPolygon.h"


typedef map<string, ConvexPolygon> PolygonMap;

namespace CMD {
    const string
            POLYGON = "polygon",
            DELETE = "delete",
            PRINT = "print",
            AREA = "area",
            PERIMETER = "perimeter",
            VERTICES = "vertices",
            CENTROID = "centroid",
            SETCOL = "setcol",
            INTERSECTION = "intersection",
            UNION = "union",
            INSIDE = "inside",
            BBOX = "bbox",
            LIST = "list",
            SAVE = "save",
            LOAD = "load",
            DRAW = "draw";
}

const string OUT_DIR = "out/";

namespace IMG {
    constexpr int HEIGHT = 500;
    constexpr int WIDTH = 500;
    constexpr double BACKGROUND = 1.0;  // background color
    constexpr double POL_OPACITY = 0.7;  // polygon opacity
}


#endif //CONVEXPOLYGONS_CONSTS_H
