// ConvexPolygon class

#ifndef CONVEXPOLYGONS_CONVEXPOLYGONS_H
#define CONVEXPOLYGONS_CONVEXPOLYGONS_H

#include <vector>
#include "class/Point.h"
#include "class/RGBColor.h"
#include "class/Box.h"
#include "details/range.h"


using namespace std;


// TODO: move out member functions

class ConvexPolygon {
private:
    Points vertices;  // TODO: cyclic container?
    RGBColor color;

    static
    Points ConvexHull(Points points);

public:
    ConvexPolygon() = default;
    ConvexPolygon(const Points &points);
    ConvexPolygon(Points &&points);  // rvalue reference overload

    ConvexPolygon(const Box &box);

    unsigned long vertexCount() const;
    double area() const;
    double perimeter() const;
    Point centroid() const;
    Box boundingBox() const;

    bool empty() const { return vertices.empty(); }
    const Points &getVertices() const { return vertices; }
    const RGBColor &getColor() const { return color; }
    void setColor(double r, double g, double b) { color = {r, g, b}; }
};


inline
bool operator==(const ConvexPolygon &lhs, const ConvexPolygon &rhs) {
    return lhs.getVertices() == rhs.getVertices();
}


inline
bool operator!=(const ConvexPolygon &lhs, const ConvexPolygon &rhs) {
    return not(rhs == lhs);
}


Box boundingBox(ConstRange<ConvexPolygon> polygons);

bool isInside(const Point &P, const ConvexPolygon &pol);
bool isInside(const ConvexPolygon &pol1, const ConvexPolygon &pol2);

ConvexPolygon convexUnion(const ConvexPolygon &, const ConvexPolygon &);
ConvexPolygon operator|(const ConvexPolygon &polA, const ConvexPolygon &polB);

ConvexPolygon intersection(const ConvexPolygon &, const ConvexPolygon &);
ConvexPolygon operator&(const ConvexPolygon &, const ConvexPolygon &);


#endif //CONVEXPOLYGONS_CONVEXPOLYGONS_H
