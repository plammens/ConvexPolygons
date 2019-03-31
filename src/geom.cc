#include "geom.h"

#include <numeric>  // std::accumulate
#include <cmath>  // std::abs
#include "errors.h"
#include "details/numeric.h"


namespace geom {

    //-------- VECTOR COMPUTATIONS --------//

    double crossProd(const Vector2D &u, const Vector2D &v) {
        return u.x*v.y - u.y*v.x;
    }

    bool colinear(const Vector2D &u, const Vector2D &v) {
        return numeric::equal(u.x*v.y - u.y*v.x, 0);
    }



    //-------- POINT COMPUTATIONS --------//

    namespace comp {

        bool xCoord(const Point &A, const Point &B) {
            if (A.x != B.x) return A.x < B.x;
            return A.y < B.y;
        }


        //---- yAngle functor ----//

        bool yAngle::operator()(const Point &A, const Point &B) {
            Vector2D OA = A - origin, OB = B - origin;
            double normOA = OA.squaredNorm(), normOB = OB.squaredNorm();

            // Scaled projections onto the y-axis:
            double projA = OA.y*std::abs(OA.y)*normOB, projB = OB.y*std::abs(OB.y)*normOA;

            if (projA != projB) return (projA > projB);
            else return normOA < normOB;
        }

    }


    bool isClockwiseTurn(const Point &A, const Point &B, const Point &C) {
        Vector2D AB = B - A, AC = C - A;
        return numeric::less(crossProd(AB, AC), 0);
    }


    bool isCounterClockwiseTurn(const Point &A, const Point &B, const Point &C) {
        Vector2D AB = B - A, AC = C - A;
        return numeric::greater(crossProd(AB, AC), 0);
    }


    Point barycenter(ConstRange<Point> points) {
        if (points.empty()) throw ValueError("no points given for barycenter");

        /*
         * Here we calculate the "average" of the points, seen as vectors,
         * using a custom binary operator that converts `Point`s to `Vector2D`s along the way.
         * We convert them to vectors because points, as such, don't have a "sum" or
         * a "scalar multiplication" operation defined on them, while vectors do.
         * This way we keep an explicit distinction between points and vectors,
         * the two sister objects of an affine space (in this case, the real, euclidean,
         * two-dimensional affine space).
         *
         * In fact, below we are using the formal definition of an affine combination
         * of points: an arbitrary origin point plus the corresponding linear combination
         * of vectors (which start at the origin and end at each of the points). The result doesn't
         * depend on the origin.
         */

        const Point origin = {0, 0};
        Vector2D sumVector = std::accumulate(points.begin(), points.end(), Vector2D{0, 0},
                                             [&origin](const Vector2D &u, const Point &P) {
                                                 return u + (P - origin);
                                             });

        return origin + sumVector/boost::size(points);
    }




    //-------- SEGMENT COMPUTATIONS --------//

    //---- Internal utilities ----//

    inline
    bool _isInRange(double x, double a, double b) {
        return numeric::leq(std::min(a, b), x) and numeric::leq(x, std::max(a, b));
    }


    inline
    bool _isInSegment(const Point &P, const Segment &seg) {
        return _isInRange(P.x, seg.startPt.x, seg.endPt.x) and
                _isInRange(P.y, seg.startPt.y, seg.endPt.y);
    }


    /*
     * Representation of a line with its normal equation, Ax + By = C.
     * Used to find the intersection of segments. Intended for internal use.
     */
    struct _Line {
        double A, B, C;

        // Conversion from a Segment
        _Line(const Segment &s)
                : A(s.endPt.y - s.startPt.y), B(s.startPt.x - s.endPt.x),
                  C(A*s.startPt.x + B*s.startPt.y) {}
    };


    //---- exposed functions ----//

    IntersectResult intersect(const Segment &seg1, const Segment &seg2) {
        const _Line l1 = seg1, l2 = seg2;  // get line equations

        double det = l1.A*l2.B - l1.B*l2.A;
        if (det == 0) return false;

        // Solve by Cramer's rule:
        Point intersection;
        intersection.x = (l1.C*l2.B - l1.B*l2.C)/det;
        intersection.y = (l1.A*l2.C - l1.C*l2.A)/det;

        bool withinBounds = _isInSegment(intersection, seg1) and _isInSegment(intersection, seg2);
        return {withinBounds, intersection};
    }


    bool isInSegment(const Point &P, const Segment &seg) {
        if (not colinear(P - seg.startPt, seg.direction())) return false;
        return _isInSegment(P, seg);
    }


    //---- IntersectResult ----//

    IntersectResult::IntersectResult(bool success, const Point &intersection)
            : point(intersection), success(success) {}

}
