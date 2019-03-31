/// @file
/// Utilities for drawing polygons to `png` images

#ifndef CONVEXPOLYGONS_DRAW_H
#define CONVEXPOLYGONS_DRAW_H

#include "class/ConvexPolygon.h"
#include "details/range.h"


/**
 * Draws polygons in `png` format to a certain file. Maps the coordinates
 * of each vertex to pixel coordinates in such a way that the bounding
 * box of the set of polygons is centered and fits completely within
 * the frame of the picture (keeping padding into account). The aspect
 * ratio of the polygons is maintained.
 *
 * @param file  name of file to write in
 * @param polygons  set of polygons to draw
 * @param fill  whether to fill with color the inside of the polygons
 * (instead of just sketching the edges)
 *
 * @pre `file` is a valid file path/name for a `png` file
 * @post the file with path `file` exists and has a drawing of `polygons`
 * @throws IOError if the file can't be opened for writing
 */
void draw(const std::string &file, ConstRange<ConvexPolygon> polygons, bool fill = false);


#endif //CONVEXPOLYGONS_DRAW_H
