//

#include <pngwriter.h>
#include <class/ConvexPolygon.h>
#include <commands.h>


void draw(const basic_string<char> &file, const vector<basic_string<char>> &polygonIDs,
          const map<string, ConvexPolygon> &polygons) {

    pngwriter png(IMG::WIDTH, IMG::HEIGHT, IMG::BACKGROUND, file.c_str());

    for (const basic_string<char> &id : polygonIDs)
        plotPolygon(getPolygon(id, polygons), png);

    png.close();
}

vector<int> flattenAndRescale(const Points &points) {
    vector<int> transformedVec(2*points.size());
    unsigned i = 0;
    for (const Point &P : points) {
        transformedVec[i++] = int(P.x);
        transformedVec[i++] = int(P.y);
    }
    return transformedVec;
}

void plotPolygon(const ConvexPolygon &pol, pngwriter &png) {
    if (not pol.vertexCount()) return;

    const Points &vertices = pol.getVertices();
    const Point &O = vertices.front();
    const RGBColor &color = pol.getColor();

    const auto end = vertices.end() - 1;
    for (auto it = vertices.begin() + 1; it < end; ++it) {
        const Point &P = it[0], &Q = it[1];
        png.filledtriangle_blend(O.x, O.y, P.x, P.y, Q.x, Q.y,
                                 IMG::POL_OPACITY, color.R(), color.G(), color.B());
    }
}
