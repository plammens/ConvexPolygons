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


#endif //CONVEXPOLYGONS_CONSTS_H
