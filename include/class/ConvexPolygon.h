#ifndef CONVEXPOLYGONS_CONVEXPOLYGONS_H
#define CONVEXPOLYGONS_CONVEXPOLYGONS_H

#include <vector>
#include <string>

#include "class/Point.h"
#include "class/RGBColor.h"
#include "consts.h"


using namespace std;


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

    const Points &getVertices() const;
    const RGBColor &getColor() const;
    void setColor(double r, double g, double b);
};


ConvexPolygon &operator|(ConvexPolygon &, const ConvexPolygon &);

ConvexPolygon convexUnion(const ConvexPolygon &, const ConvexPolygon &);

#endif //CONVEXPOLYGONS_CONVEXPOLYGONS_H
