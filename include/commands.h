#ifndef CONVEXPOLYGONS_COMMANDS_H
#define CONVEXPOLYGONS_COMMANDS_H

#include <set>


namespace CMD {
    const string
            POLYGON = "polygon",
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
            SAVE = "save",
            LOAD = "load",
            DRAW = "draw";
}

const set <string> POLYGON_CMDS = {
        CMD::POLYGON,
        CMD::PRINT,
        CMD::AREA,
        CMD::PERIMETER,
        CMD::VERTICES,
        CMD::CENTROID,
        CMD::SETCOL
};

const set <string> OP_CMDS = {
        CMD::INTERSECTION,
        CMD::UNION,
        CMD::INSIDE,
        CMD::BBOX
};

const set <string> IO_CMDS = {
        CMD::SAVE,
        CMD::LOAD,
        CMD::DRAW
};

#endif //CONVEXPOLYGONS_COMMANDS_H
