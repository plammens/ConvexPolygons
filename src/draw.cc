#include "details/draw.h"

#include <pngwriter.h>
#include "consts.h"
#include "details/utils.h"



//-------- INTERNAL UTILITIES --------//

//---- Scale helper ----//

/*
 * Utility functor to map vertices from a set of polygons to their pixel-coordinates.
 * Scales the coordinates appropriately so that the bounding box of the given
 * polygons fits the image completely, centered and maintaining the aspect ratio.
 */
class _ScaleHelper {
public:
    // Constructs a scale helper from a set of polygons. Calculates their bounding box
    // and sets the internal variables accordingly.
    _ScaleHelper(ConstRange<ConvexPolygon> polygons);

    int scaleX(double x) const;  // calculate the pixel x-coord. corresponding to this x-coord.
    int scaleY(double y) const;  // calculate the pixel y-coord. corresponding to this y-coord.
    std::pair<int, int> operator()(const Point &P) const;  // both at once

private:
    double minX, minY, maxLength;
    int xOffset, yOffset;
};


_ScaleHelper::_ScaleHelper(ConstRange<ConvexPolygon> polygons) {
    Box bBox = boundingBox(polygons);
    Point SW = bBox.SW(), NE = bBox.NE();
    double xLength = NE.x - SW.x, yLength = NE.y - SW.y;

    minX = SW.x; minY = SW.y;
    maxLength = std::max(xLength, yLength);
    xOffset = img::PADDING + int(round(img::DRAW_SIZE.X*(1 - xLength/maxLength)/2));
    yOffset = img::PADDING + int(round(img::DRAW_SIZE.Y*(1 - yLength/maxLength)/2));
}


int _ScaleHelper::scaleX(double x) const {
    if (maxLength == 0) return img::CENTER.X;
    return xOffset + int(round(img::DRAW_SIZE.X*(x - minX)/maxLength));
}


int _ScaleHelper::scaleY(double y) const {
    if (maxLength == 0) return img::CENTER.Y;
    return yOffset + int(round(img::DRAW_SIZE.Y*(y - minY)/maxLength));
}


std::pair<int, int> _ScaleHelper::operator()(const Point &P) const {
    return {scaleX(P.x), scaleY(P.y)};
}


//---- draw helper ----//

// Draws (and fills, if `fill` is true) a single polygon, scaling its coordinates
// with the given scale helper.
void _draw(pngwriter &png, const ConvexPolygon &pol, const _ScaleHelper &scale, const bool fill) {
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
                                     img::POL_OPACITY, color.R(), color.G(), color.B());
        else
            png.line(x1, y1, x2, y2, color.R(), color.G(), color.B());
    }
}




//-------- DRAW --------//

void draw(const std::string &file, ConstRange<ConvexPolygon> polygons, const bool fill) {
    checkFileForWriting(file);
    pngwriter png(img::SIZE.X, img::SIZE.Y, img::BACKGROUND, file.c_str());

    if (not polygons.empty()) {
        _ScaleHelper scale(polygons);
        for (const ConvexPolygon &pol : polygons)
            _draw(png, pol, scale, fill);
    }

    png.close();
}





