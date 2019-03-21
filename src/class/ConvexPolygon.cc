#include <algorithm>  // std::sort
#include <numeric>  // std::accumulate
#include <iostream>
#include <boost/range/adaptors.hpp>  // boost::adaptors::filter

#include "class/ConvexPolygon.h"
#include "geom.h"
#include "utils.h"


using namespace std;


// ------------------- static functions ------------------------------

Points ConvexPolygon::ConvexHull(Points &points) {
    assert(not points.empty());

    const auto begin = points.begin(), end = points.end();  // aliasing
    // Get point with lowest y coordinate:
    const Point P0 = *min_element(begin, end, PointComp::yCoord);
    // Sort the points in decreasing order of the angle they form with x-axis (relative to P0):
    sort(begin, end, PointComp::xAngle(P0, true));

    // Graham scan:
    Points hull{P0};  // starting point
    for (auto it = begin + 1; it < end; ++it) {
        if (*it == hull.back()) continue;  // skip duplicates
        while (hull.size() >= 2 and not isClockwiseTurn(hull.end()[-2], hull.end()[-1], *it))
            hull.pop_back();
        hull.push_back(*it);
    }

    hull.push_back(P0);  // complete the cycle
    return hull;
}


// --------------------- member functions ------------------------

// Constructs a convex polygon from a given list of points with a Graham scan
ConvexPolygon::ConvexPolygon(Points &points) {
    if (points.empty()) return;
    vertices = ConvexHull(points);
}

ConvexPolygon::ConvexPolygon(const Box &box) {
    vertices = {box.SW(), box.NW(), box.NE(), box.SE()};
    vertices = ConvexHull(vertices);
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
    return barycenter(vertices.begin(), vertices.end() - 1);
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



// ------------------ non-member functions ------------------------

Box boundingBox(Range<ConvexPolygon> polygons) {
    // skip empty polygons:
    polygons = boost::adaptors::filter(polygons, [](const ConvexPolygon &pol){ return not pol.empty(); });
    // if, after filtering, polygons is empty, throw an error
    if (polygons.empty()) throw ValueError("bounding box undefined for empty set");

    Point SW = polygons.begin()->getVertices()[0], NE = SW;  // Initialization
    for (const ConvexPolygon &pol : polygons) {
        ConvexPolygon bbox = pol.boundingBox();
        SW = bottomLeft(SW, pol.boundingBox().getVertices()[0]);  // TODO: subclass?
        NE = upperRight(NE, pol.boundingBox().getVertices()[2]);
    }

    Point NW = {SW.x, NE.y};
    Point SE = {NE.x, SW.y};

    return {SW, NW, NE, SE};
}


bool isInside(const Point &P, const ConvexPolygon &pol) {
    if (pol.empty()) return false;

    const Points &vertices = pol.getVertices();
    const Point &O = vertices[0];

    // Special cases:
    if (pol.vertexCount() == 1) return P == O;
    if (pol.vertexCount() == 2) return isInSegment(P, {O, vertices[1]});

    // Binary search:
    unsigned long left = 1, right = pol.vertexCount() - 1;
    while (right - left > 1) {
        unsigned long mid = (left + right)/2;
        if (isClockwiseTurn(O, vertices[mid], P)) left = mid;
        else if (isCounterClockwiseTurn(O, vertices[mid], P)) right = mid;
        else return isInSegment(P, {O, vertices[mid]});
    }

    const Point &leftVertex = vertices[left], &rightVertex = vertices[right];  // aliases
    return isClockwiseTurn(O, leftVertex, P)
           and isClockwiseTurn(leftVertex, rightVertex, P)
           and isClockwiseTurn(rightVertex, O, P);
}


bool isInside(const ConvexPolygon &pol1, const ConvexPolygon &pol2) {
    const Points &vertices1 = pol1.getVertices();
    for (const Point &P : vertices1)
        if (not isInside(P, pol2)) return false;
    return true;
}


ConvexPolygon convexUnion(const ConvexPolygon &pol1, const ConvexPolygon &pol2) {
    Points points;
    extend(points, pol1.getVertices(), pol2.getVertices());
    return ConvexPolygon(points);
}


ConvexPolygon operator|(const ConvexPolygon &polA, const ConvexPolygon &polB) {
    return convexUnion(polA, polB);
}


ConvexPolygon intersection(const ConvexPolygon &pol1, const ConvexPolygon &pol2) {
    Points intersectionPoints;

    const Points &v1 = pol1.getVertices(), &v2 = pol2.getVertices();

    for (const Point &P : v1)
        if (isInside(P, pol2)) intersectionPoints.push_back(P);
    for (const Point &P : v2)
        if (isInside(P, pol1)) intersectionPoints.push_back(P);

    const auto end2 = v2.end() - 1;
    const auto end1 = v1.end() - 1;
    for (auto it1 = v1.begin(); it1 < end1; ++it1) {
        for (auto it2 = v2.begin(); it2 < end2; ++it2) {
            auto intersection = intersect({it1[0], it1[1]}, {it2[0], it2[1]});
            if (intersection.success)
                intersectionPoints.push_back(intersection.result);
        }
    }

    return ConvexPolygon(intersectionPoints);
}


ConvexPolygon operator&(const ConvexPolygon &pol1, const ConvexPolygon &pol2) {
    return intersection(pol1, pol2);
}

