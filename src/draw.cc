//

#include <pngwriter.h>
#include <class/ConvexPolygon.h>
#include <commands.h>
#include <utils.h>
#include "draw.h"


void draw(const basic_string<char> &file, const vector<basic_string<char>> &polygonIDs, const map<string, ConvexPolygon> &polygons) {
    pngwriter png(500, 500, 1.0, file.c_str());
    png.circle(250, 250, 200, 1.0, 0.0, 0.0);

    for (const basic_string<char> &id : polygonIDs) {
        const ConvexPolygon &pol = getPolygon(id, polygons);
        if (not pol.vertexCount()) continue;

        vector<Point> vertices = pol.getVertices();
        vertices.push_back(vertices.front());
        vector<double> pointSequence = flatten(vertices);

        RGBColor color = pol.getColor();

        png.polygon(reinterpret_cast<int *>(pointSequence.data()), vertices.size(),
                    color.R(), color.G(), color.B());
    }

    png.close();
}

vector<double> flatten(const Points &points) {
    vector<double> flattened(2*points.size());
    unsigned i = 0;
    for (const Point &P : points) {
        flattened[i++] = P.x;
        flattened[i++] = P.y;
    }
    return flattened;
}