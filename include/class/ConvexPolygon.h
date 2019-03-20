#ifndef CONVEXPOLYGONS_CONVEXPOLYGONS_H
#define CONVEXPOLYGONS_CONVEXPOLYGONS_H

#include <vector>
#include <string>

#include "class/Point.h"
#include "class/RGBColor.h"


using namespace std;


// TODO: move out member functions

class ConvexPolygon {
private:
    Points vertices;
    RGBColor color;

    static
    Points ConvexHull(Points &points);

public:
    ConvexPolygon() = default;
    ConvexPolygon(Points &points);

    unsigned long vertexCount() const;
    bool empty() const;
    double area() const;
    double perimeter() const;
    Point centroid() const;
    ConvexPolygon boundingBox() const;

    ConvexPolygon &convexUnion(const ConvexPolygon &);
    ConvexPolygon &intersection(const ConvexPolygon &);

    const Points &getVertices() const;
    const RGBColor &getColor() const;
    void setColor(double r, double g, double b);
};


// Shortcut for union
ConvexPolygon &operator|(ConvexPolygon &, const ConvexPolygon &);

ConvexPolygon convexUnion(const ConvexPolygon &, const ConvexPolygon &);

bool isInside(const Point &P, const ConvexPolygon &pol);
bool isInside(const ConvexPolygon &first, const ConvexPolygon &second);

#endif //CONVEXPOLYGONS_CONVEXPOLYGONS_H
