//

#include "draw.h"
#include "utils.h"


void draw(const string &file, Range<ConvexPolygon> polygons) {
    checkFileForWriting(file);
    pngwriter png(IMG::X_SIZE, IMG::Y_SIZE, IMG::BACKGROUND, file.c_str());

    if (not polygons.empty()) {
        ScaleHelper scale(polygons);
        for (const ConvexPolygon &pol : polygons)
            fillPolygon(png, pol, scale);
    }

    png.close();
}


void fillPolygon(pngwriter &png, const ConvexPolygon &pol, const ScaleHelper &scale) {
    if (pol.empty()) return;

    // Some aliases:
    const Points &vertices = pol.getVertices();
    const RGBColor &color = pol.getColor();
    const Point &O = vertices.front();  // origin from which to draw triangles
    const int x0 = scale.scaleX(O.x), y0 = scale.scaleY(O.y);  // scaled origin coordinates

    // Fill the polygon as a partition of triangles:
    const auto end = vertices.end() - 1;
    for (auto it = vertices.begin(); it < end; ++it) {
        const Point &P = it[0], &Q = it[1];  // Just some aliasing
        // Calculate the scaled pixel-position of P and Q:
        int x1 = scale.scaleX(P.x), y1 = scale.scaleY(P.y);
        int x2 = scale.scaleX(Q.x), y2 = scale.scaleY(Q.y);

        // Fill the triangle O-P-Q:
        png.filledtriangle_blend(x0, y0, x1, y1, x2, y2,
                                 IMG::POL_OPACITY, color.R(), color.G(), color.B());
    }
}


ScaleHelper::ScaleHelper(Range<ConvexPolygon> polygons) {
    ConvexPolygon bBox = boundingBox(polygons);
    Point SW = bBox.getVertices()[0], NE = bBox.getVertices()[2];
    minX = SW.x;
    minY = SW.y;
    double xLength = NE.x - SW.x, yLength = NE.y - SW.y;
    maxLength = max(xLength, yLength);
    xOffset = IMG::PADDING + int(IMG::X_DRAW_SIZE*(1 - xLength/maxLength)/2);
    yOffset = IMG::PADDING + int(IMG::Y_DRAW_SIZE*(1 - yLength/maxLength)/2);
}


int ScaleHelper::scaleX(double x) const {
    return xOffset + int(IMG::X_DRAW_SIZE*(x - minX)/maxLength);
}


int ScaleHelper::scaleY(double y) const {
    return yOffset + int(IMG::Y_DRAW_SIZE*(y - minY)/maxLength);
}


pair<int, int> ScaleHelper::operator()(const Point &P) const {
    return {scaleX(P.x), scaleY(P.y)};
}

