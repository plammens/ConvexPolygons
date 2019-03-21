//

#include <algorithm>
#include <pngwriter.h>
#include <class/ConvexPolygon.h>
#include <commands.h>
#include "utils.h"


void draw(const string &file, const Range<ConvexPolygon> polygons) {
    checkFileForWriting(file);
    pngwriter png(IMG::SIZE, IMG::SIZE, IMG::BACKGROUND, file.c_str());
    ScaleHelper scale(polygons);

    for (const ConvexPolygon &pol : polygons)
        plotPolygon(png, pol, scale);

    png.close();
}


void plotPolygon(pngwriter &png, const ConvexPolygon &pol, const ScaleHelper &scale) {
    if (not pol.vertexCount()) return;

    const Points &vertices = pol.getVertices();
    const RGBColor &color = pol.getColor();
    const Point &O = vertices.front();  // origin from which to draw triangles
    const int x0 = scale(O.x), y0 = scale(O.y);  // scaled origin coordinates

    // Plot the polygon as a partition of triangles:
    const auto end = vertices.end() - 1;
    for (auto it = vertices.begin(); it < end; ++it) {
        const Point &P = it[0], &Q = it[1];  // Just some aliasing
        png.filledtriangle_blend(x0, y0, scale(P.x), scale(P.y), scale(Q.x), scale(Q.y),
                                 IMG::POL_OPACITY, color.R(), color.G(), color.B());
    }
}

ScaleHelper::ScaleHelper(const Range<ConvexPolygon> polygons) {
    ConvexPolygon bBox = boundingBox(polygons);
    Point SW = bBox.getVertices()[0], NE = bBox.getVertices()[3];
    minCoord = min(SW.x, SW.y);
    totalLength = max(NE.x, NE.y) - minCoord;
}


int ScaleHelper::operator()(double coord) const {
    return int(IMG::PADDING + IMG::DRAW_SIZE*(coord - minCoord)/totalLength);
}

