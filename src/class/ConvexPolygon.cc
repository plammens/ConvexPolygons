#include <algorithm>
#include <iostream>
#include <class/ConvexPolygon.h>


#include "utils.h"


using namespace std;


Points ConvexPolygon::ConvexHull(Points &points) {
    assert(not points.empty());

    const auto begin = points.begin(), end = points.end();  // aliasing
    // Get point with lowest y coordinate:
    const Point P0 = *min_element(begin, end, PointComp::yCoord);
    // Sort the points in decreasing order of the angle they form with x-axis (relative to P0):
    sort(begin, end, PointComp::xAngle(P0, true));

    // Graham scan initialization:
    Points hull {P0};  // starting point
    auto it = begin + 1;
    for (; it < end and *it == P0; ++it);  // skip duplicates
    if (it < end) hull.push_back(*it);  // second point

    // Main part of Graham scan:
    for (++it; it < end; ++it) {
        if (not isClockwiseTurn(hull.end()[-2], hull.end()[-1], *it))
            hull.pop_back();
        hull.push_back(*it);
    }

    hull.push_back(P0);  // Complete cycle
    return hull;
}


// Constructs a convex polygon from a given list of points with a Graham scan
ConvexPolygon::ConvexPolygon(Points &points) {
    if (points.empty()) return;
    vertices = ConvexHull(points);
}


// Returns the number of vertices in the polygon
unsigned long ConvexPolygon::vertexCount() const {
    if (vertices.empty()) return 0;
    return vertices.size() - 1;
}


// Returns the area of the polygon
double ConvexPolygon::area() const {
    // We use the shoelace formula for calculating the area
    double sum = 0;
    const auto end = vertices.end() - 1;
    for (auto it = vertices.begin(); it < end; ++it)
        sum += (it[1].x - it[0].x)*(it[1].y + it[0].y);
    return abs(sum/2);
}


// Returns perimeter of polygon
double ConvexPolygon::perimeter() const {
    // Sum of euclidean distance between pairs of adjacent points
    double sum = 0;
    const auto end = vertices.end() - 1;
    for (auto it = vertices.begin(); it < end; ++it)
        sum += distance(it[0], it[1]);
    return sum;
}


Point ConvexPolygon::centroid() const {
    return barycenter(vertices);
}

ConvexPolygon ConvexPolygon::boundingBox() const {
    if (vertices.empty()) throw ValueError("bounding box undefined for 0-gon");

    // SW: south-west; NE: north-east; etc.
    Point SW = accumulate(vertices.begin(), vertices.end(), vertices.front(), bottomLeft);
    Point NE = accumulate(vertices.begin(), vertices.end(), vertices.front(), upperRight);
    Point NW = {SW.x, NE.y};
    Point SE = {NE.x, SW.y};

    ConvexPolygon bBox;
    bBox.vertices = {SW, NW, NE, SE};
    return bBox;
}


ConvexPolygon &ConvexPolygon::convexUnion(const ConvexPolygon &other) {
    extend(vertices, other.getVertices());
    vertices = ConvexHull(vertices);
    return *this;
}


ConvexPolygon &operator|(ConvexPolygon &polA, const ConvexPolygon &polB) {
    return polA.convexUnion(polB);
}


// ---------------- Getters and setters ----------------


const Points &ConvexPolygon::getVertices() const { return vertices; }


const RGBColor &ConvexPolygon::getColor() const { return color; }


void ConvexPolygon::setColor(double r, double g, double b) { color = {r, g, b}; }


bool ConvexPolygon::empty() const {
    return vertices.empty();
}
