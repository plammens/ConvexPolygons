#include "class/ConvexPolygon.h"

#include <algorithm>  // std::sort
#include <numeric>  // std::accumulate
#include <iterator>
#include <boost/range/adaptors.hpp> // boost::adaptors::filter, ::sliced, ::uniqued
#include "geom.h"  // segment intersection
#include "details/utils.h"  // extend

using namespace geom;


//-------- MEMBER FUNCTIONS --------//

//---- Constructors ----//

ConvexPolygon::ConvexPolygon(const Points &points) : vertices(ConvexHull(points)) {}

ConvexPolygon::ConvexPolygon(Points &&points) : vertices(ConvexHull(move(points))) {}

ConvexPolygon::ConvexPolygon(const Box &box) {
    vertices = {box.SW(), box.NW(), box.NE(), box.SE(), box.SW()};
}


//---- Info functions ----//

unsigned long ConvexPolygon::vertexCount() const {
    if (vertices.empty()) return 0;
    return vertices.size() - 1;
    // we subtract 1 because of the repeated element at the end
}

double ConvexPolygon::area() const {
    if (empty()) return 0;

    // We use the shoelace formula for calculating the area
    double sum = 0;
    const auto end = vertices.end() - 1;
    for (auto it = vertices.begin(); it < end; ++it)
        sum += (it[1].x - it[0].x)*(it[1].y + it[0].y);  // shoelace formula
    return std::abs(sum/2);
}

double ConvexPolygon::perimeter() const {
    if (empty()) return 0;
    // avoid adding the same edge twice if the polygon is a segment:
    if (vertexCount() == 2) return (vertices[1] - vertices[0]).norm();

    double sum = 0;
    const auto end = vertices.end() - 1;
    for (auto it = vertices.begin(); it < end; ++it)
        sum += distance(it[0], it[1]);
    return sum;
}

Point ConvexPolygon::centroid() const {
    // return the barycenter of first through last points (without the duplicate):
    return barycenter(vertices | boost::adaptors::sliced(0, vertexCount()));
}

Box ConvexPolygon::boundingBox() const {
    if (vertices.empty()) throw error::ValueError("bounding box undefined for 0-gon");

    // SW: south-west; NE: north-east; etc.
    Point SW = accumulate(vertices.begin(), vertices.end(), vertices.front(), bottomLeft);
    Point NE = accumulate(vertices.begin(), vertices.end(), vertices.front(), upperRight);

    return Box(SW, NE);
}



//-------- STATIC FUNCTIONS --------//

/*
 * Calculates the convex hull of a sequence of points with the
 * Graham scan algorithm. Complexity is O(n*log(n)). Returns an empty
 * vector if the input vector is empty.
 */
Points ConvexPolygon::ConvexHull(Points points) {
    if (points.empty()) return {};

    const auto begin = points.begin(), end = points.end();  // aliases
    // Get point with lowest y coordinate:
    const Point P0 = *min_element(begin, end, comp::xCoord);
    // Sort the points in decreasing order of the angle they form with x-axis (relative to P0):
    sort(begin, end, comp::yAngle{P0});

    // Graham scan:
    Points hull;
    for (const Point &P : points | boost::adaptors::uniqued) {  // the uniqued adaptor skips duplicates
        while (hull.size() >= 2 and not isClockwiseTurn(hull.end()[-2], hull.end()[-1], P))
            hull.pop_back();
        hull.push_back(P);
    }

    hull.push_back(hull.front());  // complete the cycle
    return hull;
}



//-------- ASSOCIATED NONMEMBER FUNCTIONS --------//

Box boundingBox(ConstRange<ConvexPolygon> polygons) {
    // skip empty polygons, and if after filtering, polygons is empty, throw an error
    polygons = boost::adaptors::filter(polygons, [](const ConvexPolygon &pol){ return not pol.empty(); });
    if (polygons.empty()) throw error::ValueError("bounding box undefined for empty set");

    // Find out the bottom-left (SW) and upper-right (NE) corners of the box:
    Point SW = polygons.begin()->getVertices()[0], NE = SW;  // Initialization
    for (const ConvexPolygon &pol : polygons) {
        const Box &&box = pol.boundingBox();
        SW = bottomLeft(SW, box.SW());  // if box.SW() is further down or to the left, update
        NE = upperRight(NE, box.NE());  // if box.NE() is further up or to the right, update
    }

    return Box(SW, NE);
}


//---- isInside ----//

bool isInside(const Point &P, const ConvexPolygon &pol) {
    if (pol.empty()) return false;

    const Points &vertices = pol.getVertices();
    const Point &O = vertices[0];

    // Special cases:
    if (pol.vertexCount() == 1) return P == O;
    if (pol.vertexCount() == 2) return isInSegment(P, {O, vertices[1]});


    /*
     * Here we begin a binary search: given a fixed vertex O (in this case the
     * first vertex), and starting with the two vertices that are adjacent to O,
     * at every iteration we bisect the polygon by tracing a segment between O and the
     * median of the left and right vertices; then, we test whether `P` is to the
     * left or to the right of the bisector segment, and we update the indices
     * accordingly. We end up with a triangle, one of whose edges lies on the polygon.
     */

    unsigned long left = 1, right = pol.vertexCount() - 1;
    while (right - left > 1) {
        unsigned long mid = (left + right)/2;
        if      (isClockwiseTurn(O, vertices[mid], P))          left = mid;
        else if (isCounterClockwiseTurn(O, vertices[mid], P))   right = mid;
        else return isInSegment(P, {O, vertices[mid]});
    }

    // Return whether P is in the final triangle, by testing if P is on the right side of each edge:
    const Point &leftVertex = vertices[left], &rightVertex = vertices[right];
    return not isCounterClockwiseTurn(O, leftVertex, P) and
           not isCounterClockwiseTurn(leftVertex, rightVertex, P) and
           not isCounterClockwiseTurn(rightVertex, O, P);
}


bool isInside(const ConvexPolygon &pol1, const ConvexPolygon &pol2) {
    const Points &vertices1 = pol1.getVertices();
    for (const Point &P : vertices1)
        if (not isInside(P, pol2)) return false;
    return true;
}


//---- Convex union ----//

ConvexPolygon convexUnion(const ConvexPolygon &pol1, const ConvexPolygon &pol2) {
    // We simply merge the vertices and calculate the convex hull:
    Points points;
    extend(points, pol1.getVertices(), pol2.getVertices());
    return ConvexPolygon(move(points));
}


ConvexPolygon operator|(const ConvexPolygon &polA, const ConvexPolygon &polB) {
    return convexUnion(polA, polB);
}



//---- Intersection ----//

/*
 * Internal subroutine for `intersection` that calculates intersection points between
 * the edges of the two polygons (and appends them to `intersectionPoints`). The
 * time complexity of this algorithm is linear.
 */
inline
void _intersectionSweepLine(const ConvexPolygon &pol1, const ConvexPolygon &pol2,
                            Points &intersectionPoints) {

    // aliases:
    const Points &v1 = pol1.getVertices(), &v2 = pol2.getVertices();

    /*
     * Throughout the algorithm, we keep track of two edges on each polygon:
     * one edge on the top half and one on the bottom half of the polygon. We
     * do this by keeping track of two iterators for each polygon, each of which
     * represents the start-point of an edge.
     *
     * The top edges will advance in clockwise order, while the bottom edges advance
     * in counter-clockwise order (hence, their corresponding iterators will be reverse).
     */

    auto it1Top = v1.begin(), it2Top = v2.begin();
    // reverse iterators for bottom edges (advancing counterclockwise):
    auto it1Bottom = v1.rbegin(), it2Bottom = v2.rbegin();

    // Some lambdas for commodity (these get the edge pointed at by an iterator):
    auto edge1Top =     [&it1Top]()   { return Segment{it1Top[0], it1Top[1]}; };
    auto edge1Bottom =  [&it1Bottom](){ return Segment{it1Bottom[0], it1Bottom[1]}; };
    auto edge2Top =     [&it2Top]()   { return Segment{it2Top[0], it2Top[1]}; };
    auto edge2Bottom =  [&it2Bottom](){ return Segment{it2Bottom[0], it2Bottom[1]}; };

    // Lambdas to calculate the intersection of a pair of edges:
    auto intsTT = [&](){ return geom::intersect(edge1Top(), edge2Top()); };
    auto intsTB = [&](){ return geom::intersect(edge1Top(), edge2Bottom()); };
    auto intsBT = [&](){ return geom::intersect(edge1Bottom(), edge2Top()); };
    auto intsBB = [&](){ return geom::intersect(edge1Bottom(), edge2Bottom()); };

    // Add first four potential intersection points:
    for (const IntersectResult &ir : {intsTT(), intsTB(), intsBT(), intsBB()})
        if (ir) intersectionPoints.push_back(ir.getPoint());

    /*
     * Here we start a sweepline algorithm. At each iteration, we check the intersections
     * between the four pairs of segments, and then we increment the edge (represented
     * by an iterator to its start-point) which has the end-point with the lowest `x`
     * coordinate (hence the "sweepline"; it's like advancing a vertical line from left to
     * right). We stop when we reach either polygon's rightmost vertex --- which happens
     * when both iterators (one from the top and one from the bottom) coincide.
     */

    while (not (it1Top == it1Bottom.base() or it2Top == it2Bottom.base())) {
        // Fond out the edge whose end point has the lowest x coordinate:
        double xCoords[4] = {it1Top[1].x, it1Bottom[1].x, it2Top[1].x, it2Bottom[1].x};
        unsigned minIndex = std::min_element(std::begin(xCoords), std::end(xCoords)) - std::begin(xCoords);

        // Increment the corresponding iterator and calculate new intersections:
        IntersectResult ints[2];  // potential new intersection points
        if      (minIndex == 0) { ++it1Top;     ints[0] = intsTT(); ints[1] = intsTB(); }
        else if (minIndex == 1) { ++it1Bottom;  ints[0] = intsBT(); ints[1] = intsBB(); }
        else if (minIndex == 2) { ++it2Top;     ints[0] = intsTT(); ints[1] = intsBT(); }
        else if (minIndex == 3) { ++it2Bottom;  ints[0] = intsTB(); ints[1] = intsBB(); }

        // Update intersection points:
        for (const IntersectResult &result : ints)
            if (result) intersectionPoints.push_back(result.getPoint());
    }
}


ConvexPolygon intersection(const ConvexPolygon &pol1, const ConvexPolygon &pol2) {
    if (pol1.empty() or pol2.empty()) return {};

    Points intersectionPoints;
    const Points &v1 = pol1.getVertices(), &v2 = pol2.getVertices();

    // Find the vertices of one polygon that are inside the other, in O(m·log(n)) each:
    for (const Point &P : v1)
        if (isInside(P, pol2)) intersectionPoints.push_back(P);
    for (const Point &P : v2)
        if (isInside(P, pol1)) intersectionPoints.push_back(P);

    // Add the intersection points between pairs of edges, in O(n + m):
    if (pol1.vertexCount() > 1 and pol2.vertexCount() > 1)
        _intersectionSweepLine(pol1, pol2, intersectionPoints);

    // Return the convex hull of all the intersection points:
    return ConvexPolygon(move(intersectionPoints));
}


ConvexPolygon operator&(const ConvexPolygon &pol1, const ConvexPolygon &pol2) {
    return intersection(pol1, pol2);
}



//---- Equality operators ----//

bool operator==(const ConvexPolygon &lhs, const ConvexPolygon &rhs) {
    return lhs.getVertices() == rhs.getVertices();
}

bool operator!=(const ConvexPolygon &lhs, const ConvexPolygon &rhs) {
    return not(rhs == lhs);
}

