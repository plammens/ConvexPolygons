
#include <draw.h>

#include "draw.h"
#include "utils.h"


void draw(const string &file, Range<ConvexPolygon> polygons, bool fill) {
    checkFileForWriting(file);
    pngwriter png(IMG::X_SIZE, IMG::Y_SIZE, IMG::BACKGROUND, file.c_str());

    if (not polygons.empty()) {
        ScaleHelper scale(polygons);
        for (const ConvexPolygon &pol : polygons)
            drawPolygon(png, pol, scale, fill);
    }

    png.close();
}


void drawPolygon(pngwriter &png, const ConvexPolygon &pol, const ScaleHelper &scale, bool fill) {
    if (pol.empty()) return;

    // Some aliases:
    const Points &vertices = pol.getVertices();
    const RGBColor &color = pol.getColor();
    const Point &O = vertices.front();  // origin from which to draw triangles
    const int x0 = scale.scaleX(O.x), y0 = scale.scaleY(O.y);  // scaled origin coordinates

    if (pol.vertexCount() == 1) {
        png.plot(x0, y0, color.R(), color.G(), color.B());
        return;
    }

    // Fill/sketch the polygon by partitioning in triangles/segments:
    const auto end = vertices.end() - 1;
    for (auto it = vertices.begin(); it < end; ++it) {
        const Point &P = it[0], &Q = it[1];  // Just some aliasing
        // Calculate the scaled pixel-position of P and Q:
        int x1 = scale.scaleX(P.x), y1 = scale.scaleY(P.y);
        int x2 = scale.scaleX(Q.x), y2 = scale.scaleY(Q.y);

        if (fill)
            png.filledtriangle_blend(x0, y0, x1, y1, x2, y2,
                                     IMG::POL_OPACITY, color.R(), color.G(), color.B());
        else
            png.line(x1, y1, x2, y2, color.R(), color.G(), color.B());
    }
}


ScaleHelper::ScaleHelper(Range<ConvexPolygon> polygons) {
    Box bBox = boundingBox(polygons);
    Point SW = bBox.SW(), NE = bBox.NE();
    minX = SW.x; minY = SW.y;
    double xLength = NE.x - SW.x, yLength = NE.y - SW.y;
    maxLength = max(xLength, yLength);
    xOffset = IMG::PADDING + int(round(IMG::X_DRAW_SIZE*(1 - xLength/maxLength)/2));
    yOffset = IMG::PADDING + int(round(IMG::Y_DRAW_SIZE*(1 - yLength/maxLength)/2));
}


int ScaleHelper::scaleX(double x) const {
    if (maxLength == 0) return IMG::X_CENTER;
    return xOffset + int(round(IMG::X_DRAW_SIZE*(x - minX)/maxLength));
}


int ScaleHelper::scaleY(double y) const {
    if (maxLength == 0) return IMG::Y_CENTER;
    return yOffset + int(round(IMG::Y_DRAW_SIZE*(y - minY)/maxLength));
}


pair<int, int> ScaleHelper::operator()(const Point &P) const {
    return {scaleX(P.x), scaleY(P.y)};
}

