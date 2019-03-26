#include "geom.h"

#include "details/utils.h"


SolveResult intersect(const Segment &r, const Segment &s) {
    double det = r.A()*s.B() - r.B()*s.A();
    if (numericEquals(det, 0)) return {{}, false};

    // Solve by Cramer's rule:
    Point intersection{};
    intersection.x = (r.C()*s.B() - r.B()*s.C())/det;
    intersection.y = (r.A()*s.C() - r.C()*s.A())/det;

    bool withinBounds = isInSegment(intersection, r) and isInSegment(intersection, s);
    return {intersection, withinBounds};
}


bool isInSegment(const Point &P, const Segment &r) {
    Vector2D direction = r.end() - r.start(), u = P - r.start();
    if (u.x*direction.y != u.y*direction.x) return false;
    double lambda = (numericEquals(direction.x, 0) ? u.y/direction.y : u.x/direction.x);
    return 0 <= lambda and lambda <= 1;
}


Segment::Segment(const Point &start, const Point &end) : _start(start), _end(end),
                                                         _A(end.y - start.y), _B(start.x - end.x),
                                                         _C(_A*start.x + _B*start.y) {}
