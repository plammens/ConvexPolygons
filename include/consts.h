//

#ifndef CONVEXPOLYGONS_CONSTS_H
#define CONVEXPOLYGONS_CONSTS_H

#include <boost/range/any_range.hpp>


template <typename T>
using Range = boost::any_range<const T, boost::bidirectional_traversal_tag>;

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
            DRAW = "draw";
}

namespace IO {
    constexpr auto OUT_DIR = "out/";
}

namespace IMG {  // some image constants
    constexpr int SIZE = 500;
    constexpr double BACKGROUND = 1.0;  // background color
    constexpr double POL_OPACITY = 0.6;  // polygon opacity
    constexpr int PADDING = 2;  // padding in pixels
    constexpr double DRAW_SIZE = SIZE - 2*PADDING;  // size of available drawing space
}

namespace NUM {
    constexpr double EPSILON = 1e-12; 
}


#endif //CONVEXPOLYGONS_CONSTS_H
