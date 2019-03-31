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
            /*
             * This comparison works by using the fact that the cosine
             * is monotonically decreasing in the interval [0, PI]. We want
             * to know if the angle between ĵ = (0, 1) and the vector OA
             * (let's call it α) is smaller than the angle between ĵ and
             * the vector OB (let's call it β). Thus, we have to check
             * whether
             *
             *   cos(α) = OA·ĵ/(‖OA‖‖ĵ‖) = OA.y/‖OA‖ >
             *   > OB.y/‖OB‖ = OB·ĵ/(‖OB‖‖ĵ‖) = cos(β),
             *
             * which is equivalent to checking whether
             *
             *   OA.y‖OB‖ > OB.y‖OA‖.
             *
             * To avoid having to calculate square roots, we can apply
             * the monotonously increasing function f defined by
             *
             *   f(x) = sgn(x)·x² = x/|x|·x² = x·|x|.
             *
             * Thus, we end up checking whether
             *
             *   OA.y|OA.y|·‖OB‖² > OB.y|OB.y|·‖OA‖²,
             *
             * which can be thought of as comparing the projections of each
             * vector onto the y-axis, scaled appropriately to be directly
             * comparable.
             */

            Vector2D OA = A - origin, OB = B - origin;
            double normOA = OA.squaredNorm(), normOB = OB.squaredNorm();

            // Scaled projections onto the y-axis:
            double projA = OA.y*std::abs(OA.y)*normOB, projB = OB.y*std::abs(OB.y)*normOA;

            if (projA != projB) return (projA > projB);
            else return normOA < normOB;
            // ^ in case of equality, prioritize the point closest to the origin
        }

    }


    bool isClockwiseTurn(const Point &A, const Point &B, const Point &C) {
        // we check the sign of the cross product of AB and AC
        Vector2D AB = B - A, AC = C - A;
        return numeric::less(crossProd(AB, AC), 0);
    }


    bool isCounterClockwiseTurn(const Point &A, const Point &B, const Point &C) {
        // we check the sign of the cross product of AB and AC
        Vector2D AB = B - A, AC = C - A;
        return numeric::greater(crossProd(AB, AC), 0);
    }


    Point barycenter(const ConstRange<Point> &points) {
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

    // Check whether a number x lies in the closed interval [a, b]
    inline
    bool _isInRange(double x, double a, double b) {
        return numeric::leq(std::min(a, b), x) and numeric::leq(x, std::max(a, b));
    }


    // Check whether a point is in a segment, assuming as a precondition
    // that the point lies on the line defined by the segment.
    inline
    bool _isInSegment(const Point &P, const Segment &seg) {
        return _isInRange(P.x, seg.startPt.x, seg.endPt.x) and
                _isInRange(P.y, seg.startPt.y, seg.endPt.y);
    }


    // Representation of a line with its normal equation, Ax + By = C.
    // Used to find the intersection of segments. Intended for internal use.
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

        double determinant = l1.A*l2.B - l1.B*l2.A;
        if (determinant == 0) return false;

        // Solve by Cramer's rule:
        Point intersection;
        intersection.x = (l1.C*l2.B - l1.B*l2.C)/determinant;
        intersection.y = (l1.A*l2.C - l1.C*l2.A)/determinant;

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
