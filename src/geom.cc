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


///////////////////////// EXPOSED FUNCTIONS ///////////////////////////


IntersectResult intersect(const Segment &seg1, const Segment &seg2) {
    const double A1 = seg1.endPt.y - seg1.startPt.y,
                 B1 = seg1.startPt.x - seg1.endPt.x,
                 C1 = A1*seg1.startPt.x + B1*seg2.startPt.y;

    const double A2 = seg2.endPt.y - seg2.startPt.y,
                 B2 = seg2.startPt.x - seg2.endPt.x,
                 C2 = A2*seg2.startPt.x + B2*seg2.startPt.y;

    double det = A1*B2 - B1*A2;
    if (numeric::equal(det, 0)) return {{}, false};

    // Solve by Cramer's rule:
    Point intersection;
    intersection.x = (C1*B2 - B1*C2)/det;
    intersection.y = (A1*C2 - C1*A2)/det;

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
