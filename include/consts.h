/**
 * @file
 * Shared global constants for the project.
 */

#ifndef CONVEXPOLYGONS_CONSTS_H
#define CONVEXPOLYGONS_CONSTS_H


/// Namespace for storing all recognized command keywords
namespace cmd {

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


/// Input-output related identifiers
namespace io {

    /// root directory for input-output operations:
    constexpr auto OUT_DIR = "out";

}


/**
 * Image-related identifiers.
 * This namespace contains all of the project identifiers related to
 * plotting polygons in `png` images.
 */
namespace img {

    constexpr struct { int X, Y; } SIZE{500, 500};
    constexpr int PADDING = 2;  // padding in pixels
    constexpr double BACKGROUND = 1.0;  // background color
    constexpr double POL_OPACITY = 0.6;  // polygon opacity

    constexpr struct { int X, Y; } CENTER{(SIZE.X + 1)/2, (SIZE.Y + 1)/2};
    constexpr struct { int X, Y; } DRAW_SIZE{SIZE.X - 2*PADDING, SIZE.Y - 2*PADDING};

}


/// Namespace for anything related to numerical computations
namespace numeric {
    constexpr double EPSILON = 1e-12; 
}


#endif //CONVEXPOLYGONS_CONSTS_H
