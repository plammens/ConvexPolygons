//

#include <algorithm>
#include <pngwriter.h>
#include <class/ConvexPolygon.h>
#include <commands.h>


void draw(const string &file, const vector<string> &polygonIDs,
          const map<string, ConvexPolygon> &polygons) {

    pngwriter png(IMG::SIZE, IMG::SIZE, IMG::BACKGROUND, file.c_str());
    ScaleHelper scale(polygonIDs, polygons);

    for (const string &id : polygonIDs)
        plotPolygon(png, getPolygon(id, polygons), scale);

    png.close();
}


void plotPolygon(pngwriter &png, const ConvexPolygon &pol, const ScaleHelper &scale) {
    if (not pol.vertexCount()) return;

    const Points &vertices = pol.getVertices();
    const RGBColor &color = pol.getColor();
    const Point &O = vertices.front();  // O stands for origin

    // Plot the polygon as a partition of triangles:
    const auto end = vertices.end() - 1;
    for (auto it = vertices.begin() + 1; it < end; ++it) {
        const Point &P = it[0], &Q = it[1];  // Just some aliasing
        png.filledtriangle_blend(scale(O.x), scale(O.y), scale(P.x), scale(P.y), scale(Q.x), scale(Q.y),
                                 IMG::POL_OPACITY, color.R(), color.G(), color.B());
    }
}

ScaleHelper::ScaleHelper(const vector<string> &polIDs, const PolygonMap &polygons) {
    ConvexPolygon bBox = boundingBox(polIDs, polygons);
    Point SW = bBox.getVertices()[0], NE = bBox.getVertices()[3];
    minCoord = min(SW.x, SW.y);
    totalLength = max(NE.x, NE.y) - minCoord;
}


int ScaleHelper::operator()(double coord) const {
    return int(IMG::PADDING + IMG::DRAW_SIZE*(coord - minCoord)/totalLength);
}

