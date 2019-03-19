#include <algorithm>
#include <iostream>
#include <class/ConvexPolygon.h>


#include "utils.h"


using namespace std;


Points ConvexPolygon::ConvexHull(Points &points) {
    assert(not points.empty());

    Points vertices;

    // Get point with lowest y coordinate:
    const Point P0 = *min_element(points.begin(), points.end(), PointComp::yCoord);
    vertices.push_back(P0);

    // Sort the points in decreasing order of the angle they form with x-axis (relative to P0):
    sort(points.begin(), points.end(), PointComp::xAngle(P0, true));

    vertices.push_back(P0);
    if (points.size() > 1 and points[1] != P0) vertices.push_back(points[1]);  // avoid duplicate

    for (auto it = points.begin() + 2; it < points.end(); ++it) {
        const auto hullEnd = vertices.end();  // alias
        while (vertices.size() >= 2 and not isClockwiseTurn(hullEnd[-2], hullEnd[-1], *it))
            vertices.pop_back();
        vertices.push_back(*it);
    }

    vertices.push_back(P0);  // Complete cycle
    return vertices;
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
    vertices.reserve(vertices.size() + other.vertices.size());
    vertices.insert(vertices.end(), other.vertices.begin(), other.vertices.end());
    vertices = ConvexHull(vertices);
    return *this;
}


ConvexPolygon &ConvexPolygon::convexUnion(const vector<ConvexPolygon> &others) {
    // Calculate size to reserve
    unsigned long size = vertices.size();
    for (const ConvexPolygon &pol : others) size += pol.vertices.size();
    vertices.reserve(size);  // reserve beforehand for efficiency

    // Copy contents
    for (const ConvexPolygon &pol : others)
        vertices.insert(vertices.end(), pol.vertices.begin(), pol.vertices.end());

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
