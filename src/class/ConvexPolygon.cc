#include <algorithm>
#include <iostream>
#include <class/ConvexPolygon.h>
#include <cmath>


#include "utils.h"


using namespace std;


// Constructs a convex polygon from a given list of points with a Graham scan
ConvexPolygon::ConvexPolygon(Points &points) {
    if (points.empty()) return;

    // Get point with lowest y coordinate:
    const Point P0 = *min_element(points.begin(), points.end(), PointComp::yCoord);
    // Sort the points in increasing order of the angle they form with x-axis (relative to P0):
    sort(points.begin(), points.end(), PointComp::xAngle(P0, true));

    vertices.push_back(P0);
    if (points.size() > 1 and points[1] != P0) vertices.push_back(points[1]);  // avoid duplicate

    for (auto it = points.begin() + 2; it < points.end(); ++it) {
        const auto last = vertices.end();  // alias
        while (vertices.size() >= 2 and not isClockwiseTurn(last[-2], last[-1], *it))
            vertices.pop_back();
        vertices.push_back(*it);
    }
}


// Returns the number of vertices in the polygon
unsigned long ConvexPolygon::vertexCount() const {
    return vertices.size();
}


// Returns the area of the polygon
double ConvexPolygon::area() const {
    // We use a lambda to calculate the are of the polygon with the shoelace formula
    double sum = cyclicSum(vertices,
                           [](const Point &P, const Point &Q) {
                               return (Q.x - P.x)*(Q.y + P.y);
                           });
    return abs(sum/2);
}


// Returns perimeter of polygon
double ConvexPolygon::perimeter() const {
    // Sum of euclidean distance between pairs of adjacent points
    return cyclicSum(vertices,
            // This lambda returns euclidean distance
                     [](const Point &P, const Point &Q) {
                         return distance(P, Q);
                     });
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

// ---------------- Getters and setters ----------------


const Points &ConvexPolygon::getVertices() const { return vertices; }


const RGBColor &ConvexPolygon::getColor() const { return color; }


void ConvexPolygon::setColor(double r, double g, double b) { color = {r, g, b}; }


ConvexPolygon boundingBox(const vector<ConvexPolygon> &polygons) {
    if (polygons.empty()) throw ValueError("bounding box undefined for empty set");

    Point SW = {INFINITY, INFINITY};
    Point NE = {-INFINITY, -INFINITY};
    for (const ConvexPolygon &pol : polygons) {
        SW = bottomLeft(SW, pol.boundingBox().getVertices()[0]);  // TODO: subclass?
        NE = upperRight(NE, pol.boundingBox().getVertices()[2]);
    }

    Point NW = {SW.x, NE.y};
    Point SE = {NE.x, SW.y};

    Points boxVertices = {SW, NW, NE, SE};
    return ConvexPolygon(boxVertices);
}
