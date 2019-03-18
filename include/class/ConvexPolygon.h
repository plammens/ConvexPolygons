#ifndef CONVEXPOLYGONS_CONVEXPOLYGONS_H
#define CONVEXPOLYGONS_CONVEXPOLYGONS_H

#include <vector>
#include <string>

#include "class/Point.h"
#include "class/RGBColor.h"


using namespace std;


class ConvexPolygon {
private:
    Points vertices;
    RGBColor color;

public:
    ConvexPolygon() = default;
    ConvexPolygon(Points &points);
    unsigned long vertexCount() const;

    double area() const;
    double perimeter() const;
    Point centroid() const;
    ConvexPolygon boundingBox() const;

    const Points &getVertices() const;
    const RGBColor &getColor() const;
    void setColor(double r, double g, double b);
};


ConvexPolygon boundingBox(const vector<ConvexPolygon> &polygons);


#endif //CONVEXPOLYGONS_CONVEXPOLYGONS_H
