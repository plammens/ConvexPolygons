#include "geom.h"

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
