// Some shared global constants

#ifndef CONVEXPOLYGONS_CONSTS_H
#define CONVEXPOLYGONS_CONSTS_H


// command keywords
namespace CMD {
    constexpr auto
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
            INCLUDE = "include",
            DRAW = "draw",
            PAINT = "paint";
}

namespace IO {
    constexpr auto OUT_DIR = "out/";
}

// some image constants
namespace IMG {
    constexpr int X_SIZE = 500, Y_SIZE = 500;
    constexpr int PADDING = 2;  // padding in pixels
    constexpr double BACKGROUND = 1.0;  // background color
    constexpr double POL_OPACITY = 0.6;  // polygon opacity

    constexpr int X_CENTER = (X_SIZE + 1)/2, Y_CENTER = (Y_SIZE + 1)/2;
    constexpr int X_DRAW_SIZE = X_SIZE - 2*PADDING, Y_DRAW_SIZE = Y_SIZE - 2*PADDING;
    //              ^^^ size of available drawing space
}

// numeric constants
namespace NUM {
    constexpr double EPSILON = 1e-12; 
}


#endif //CONVEXPOLYGONS_CONSTS_H
