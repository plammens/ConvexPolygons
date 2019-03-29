#include "geom.h"

#include <numeric>
#include "details/utils.h"

///////////////////////// INTERNAL HELPER FUNCTIONS ///////////////////////////


inline
bool colinear(const Vector2D &u, const Vector2D &v) {
    return numeric::equal(u.x*v.y - u.y*v.x, 0);
}


inline
bool isInRange(double x, double a, double b) {
    return numeric::leq(min(a, b), x) and numeric::leq(x, max(a, b));
}


inline
bool _isInSegment(const Point &P, const Segment &seg) {
    return isInRange(P.x, seg.startPt.x, seg.endPt.x) and
           isInRange(P.y, seg.startPt.y, seg.endPt.y);
}


// Representation of a line with its normal equation, Ax + By = C.
// Used to find the intersection of segments.
struct Line {
    double A, B, C;

    // Conversion from a Segment
    Line(const Segment &s)
            : A(s.endPt.y - s.startPt.y), B(s.startPt.x - s.endPt.x),
              C(A*s.startPt.x + B*s.startPt.y) {}
};


///////////////////////// EXPOSED FUNCTIONS ///////////////////////////


IntersectResult intersect(const Segment &seg1, const Segment &seg2) {
    const Line l1 = seg1, l2 = seg2;  // get line equations

    double det = l1.A*l2.B - l1.B*l2.A;
    if (det == 0) return {{}, false};

    // Solve by Cramer's rule:
    Point intersection;
    intersection.x = (l1.C*l2.B - l1.B*l2.C)/det;
    intersection.y = (l1.A*l2.C - l1.C*l2.A)/det;

    bool withinBounds = _isInSegment(intersection, seg1) and _isInSegment(intersection, seg2);
    return {intersection, withinBounds};
}


bool isInSegment(const Point &P, const Segment &r) {
    if (not colinear(P - r.startPt, r.direction())) return false;
    return _isInSegment(P, r);
}


Vector2D Segment::direction() const {
    return endPt - startPt;
}


// Whether vectors AB and AC are in a clockwise configuration (in that order)
bool isClockwiseTurn(const Point &A, const Point &B, const Point &C) {
    Vector2D AB = B - A, AC = C - A;
    return crossProd(AB, AC) < 0;
}


// Whether vectors AB and AC are in a clockwise configuration (in that order)
bool isCounterClockwiseTurn(const Point &A, const Point &B, const Point &C) {
    Vector2D AB = B - A, AC = C - A;
    return crossProd(AB, AC) > 0;
}


Point barycenter(ConstRange <Point> points) {
    if (points.empty()) throw ValueError("no points given for barycenter");
    // Here we calculate the "average" of the points seen as vectors.
    // We use a custom binary operator that converts `Point`s to `Vector2D`s along the way.
    Vector2D sumVector = accumulate(points.begin(), points.end(), Vector2D{0, 0},
                                    [](const Vector2D &u, const Point &P) {
                                        return u + (const Vector2D &)(P);
                                    });
    return Point{0, 0} + sumVector/boost::size(points);
}


namespace PointComp {

    // Returns whether A has a smaller y-coordinate than B
    // (and smaller x-coordinate in case of equality).
    bool yCoord(const Point &A, const Point &B) {
        if (A.y != B.y) return A.y < B.y;
        return A.x < B.x;
    }


    // Constructs a new xAngle comparison with P as origin. If `descending` is true,
    // comparison by angle (not the whole ordering) is descending.
    xAngle::xAngle(const Point &P, bool descending) : origin(P), reversed(descending) {}


    // Compares Points according to the angles that the vectors joining the origin
    // with each point form with the x-axis. Returns whether the first angle is smaller
    // (if not reversed; otherwise, vice-versa). In case the angles coincide
    // (or one of them is undefined), returns whether the first vector has smaller norm.
    // Pre: angles are in [0, PI]
    bool xAngle::operator()(const Point &A, const Point &B) {
        Vector2D OA = A - origin, OB = B - origin;
        double normOA = OA.squaredNorm(), normOB = OB.squaredNorm();
        double projA = OA.x*abs(OA.x)*normOB, projB = OB.x*abs(OB.x)*normOA;  // Scaled projections onto the x-axis

        if (projA != projB) return reversed xor (projA > projB);
        else return normOA < normOB;
    }

}