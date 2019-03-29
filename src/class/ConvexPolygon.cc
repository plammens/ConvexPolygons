#include "class/ConvexPolygon.h"

#include <algorithm>  // std::sort
#include <numeric>  // std::accumulate
#include <iterator>
#include <boost/range/adaptors.hpp> // boost::adaptors::filter, ::sliced
#include "geom.h"  // segment intersection
#include "details/utils.h"  // extend



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
    if (vertices.empty()) throw ValueError("bounding box undefined for 0-gon");

    // SW: south-west; NE: north-east; etc.
    Point SW = accumulate(vertices.begin(), vertices.end(), vertices.front(), bottomLeft);
    Point NE = accumulate(vertices.begin(), vertices.end(), vertices.front(), upperRight);

    return Box(SW, NE);
}



//-------- STATIC FUNCTIONS --------//

/*
 * Calculates the convex hull of a sequence of points with the
 * Graham scan algorithm. Complexity is O(n*log(n)).
 */
Points ConvexPolygon::ConvexHull(Points points) {
    if (points.empty()) return {};

    const auto begin = points.begin(), end = points.end();  // aliases
    // Get point with lowest y coordinate:
    const Point P0 = *min_element(begin, end, PointComp::xCoord);
    // Sort the points in decreasing order of the angle they form with x-axis (relative to P0):
    sort(begin, end, PointComp::yAngle(P0, true));

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



//-------- ASSOCIATED NONMEMBER FUNCTIONS --------//

Box boundingBox(ConstRange<ConvexPolygon> polygons) {
    // skip empty polygons, and if after filtering, polygons is empty, throw an error
    polygons = boost::adaptors::filter(polygons, [](const ConvexPolygon &pol){ return not pol.empty(); });
    if (polygons.empty()) throw ValueError("bounding box undefined for empty set");

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
 * the edges of the two polygons and appends them to `intersectionPoints`
 */
inline
void _intersectionSweepLine(const ConvexPolygon &pol1, const ConvexPolygon &pol2,
                            Points &intersectionPoints) {
    auto it1L = pol1.getVertices().begin(), it2L = pol2.getVertices().begin();
    auto it1R = pol1.getVertices().rbegin(), it2R = pol2.getVertices().rbegin();

    // Some lambdas for commodity:
    auto edge1Left = [&it1L](){ return Segment{it1L[0], it1L[1]}; };
    auto edge1Right = [&it1R](){ return Segment{it1R[0], it1R[1]}; };
    auto edge2Left = [&it2L](){ return Segment{it2L[0], it2L[1]}; };
    auto edge2Right = [&it2R](){ return Segment{it2R[0], it2R[1]}; };

    auto res1 = [&](){ return intersect(edge1Left(), edge2Left()); };
    auto res2 = [&](){ return intersect(edge1Left(), edge2Right()); };
    auto res3 = [&](){ return intersect(edge1Right(), edge2Left()); };
    auto res4 = [&](){ return intersect(edge1Right(), edge2Right()); };

    // Sweepline:=
    while (not (it1L == it1R.base() or it2L == it2R.base())) {
        for (const IntersectResult &ir : {res1(), res2(), res3(), res4()})
            if (ir.success) intersectionPoints.push_back(ir.point);

        // Increment the edge whose end point has the lowest x coordinate:
        if      (it1L[1].x <= it1R[1].x and it1L[1].x <= it2L[1].x and it1L[1].x <= it2R[1].x) ++it1L;
        else if (it1R[1].x <= it1L[1].x and it1R[1].x <= it2L[1].x and it1R[1].x <= it2R[1].x) ++it1R;
        else if (it2L[1].x <= it1L[1].x and it2L[1].x <= it1R[1].x and it2L[1].x <= it2R[1].x) ++it2L;
        else ++it2R;
    }
}

ConvexPolygon intersection(const ConvexPolygon &pol1, const ConvexPolygon &pol2) {
    if (pol1.empty() or pol2.empty()) return {};

    Points intersectionPoints;
    const Points &v1 = pol1.getVertices(), &v2 = pol2.getVertices();

    for (const Point &P : v1)
        if (isInside(P, pol2)) intersectionPoints.push_back(P);
    for (const Point &P : v2)
        if (isInside(P, pol1)) intersectionPoints.push_back(P);

    if (pol1.vertexCount() > 1 and pol2.vertexCount() > 1)
        _intersectionSweepLine(pol1, pol2, intersectionPoints);

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

