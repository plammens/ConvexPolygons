/// @file
/// Geometric utilities of various sorts

#ifndef CONVEXPOLYGONS_GEOM_H
#define CONVEXPOLYGONS_GEOM_H

#include "class/Point.h"
#include "class/Vector2D.h"
#include "details/range.h"


/// Namespace for geometric utilities of various sorts
namespace geom {

    //-------- VECTOR COMPUTATIONS --------//

    /**
     * Two-dimensional cross product.
     * @param u  left operand of the cross product
     * @param v  right operand of the cross product
     * @return the `z` component of the cross product:
     * \f$ (u_x, u_y, 0)\times(v_x, v_y, 0) =  u_x v_y - u_y v_x \f$.
     */
    double crossProd(const Vector2D & u, const Vector2D& v);

    /**
     * Whether two vectors are colinear
     * @param u,v  vectors under consideration
     * @return whether `u` and `v` are colinear
     */
    bool colinear(const Vector2D &u, const Vector2D &v);



    //-------- POINT COMPUTATIONS --------//

    //! @name Point computations
    //! Utilities for calculations involving points
    ///@{

    /// Comparison functions (and functors)
    namespace comp {

        /**
         * Strict total order comparison for points based on the
         * `x` coordinate. Compares the `x` coordinate and the `y`
         * coordinate in case of equality. Equivalent to the lexicographical
         * ordering given by applying `std::tie` to `Point::x`, `Point::y`.
         * @param A,B  points to be compared
         * @return whether `A` has a lower `x` coordinate than `B`
         * (or a lower `y` coordinate in case of equality).
         */
        bool xCoord(const Point &A, const Point &B);


        /**
         * Functor for a comparator that, given an origin point,
         * compares points based on the angle they form with
         * the y-axis. That is, every point \f$ P \f$ is compared
         * based on the angle that \f$ \overrightarrow{OP} \f$
         * forms with the unit vector \f$ \hat{\jmath} = (0, 1) \f$,
         * where \f$ O \f$ is the instance's origin point. \f$ A \f$
         * comes before \f$ B \f$ in this strict total order iff the angle
         * that \f$ \overrightarrow{OA} \f$ forms with the y-axis is
         * strictly smaller than the angle formed by
         * \f$ \overrightarrow{OB} \f$.
         *
         * In case of equality, points that are closer to the origin
         * are prioritized.
         *
         * @pre all of the vectors starting at the origin and ending
         * at each of the points to be compared form an angle with the
         * y-axis that is within the interval \f$ [0, \pi] \f$. Equivalently,
         * every point to be compared is to the right of the origin.
         */
        struct yAngle {
            Point origin;  ///< origin from which vectors to compared points start

            /**
             * Strict total ordering comparison function.
             * @param A,B points to be compared
             * @return whether `A` comes before `B` in the ordering defined
             * by this instance. See the docs for geom::comp::yAngle for details.
             * @pre see the docs for geom::comp::yAngle.
             */
            bool operator()(const Point &A, const Point &B);
        };

    }


    /**
     * Whether a sequence of three points forms a (strictly) clockwise turn
     * @param A,B,C  points under consideration
     * @return  Whether the segment \f$ BC \f$ forms a counter-clockwise turn
     * respect to the segment \f$ AB \f$. Equivalently, whether the vector
     * \f$ \overrightarrow{AC} \f$ lies clockwise with respect to
     * \f$ \overrightarrow{AB} \f$ &mdash; i.e., the angle from the latter
     * to the former is within the open  interval \f$ ]0, \pi[ \f$ .
     */
    bool isClockwiseTurn(const Point &A, const Point &B, const Point &C);


    /**
     * Whether a sequence of three points forms a (strictly) counter-clockwise turn
     * @param A,B,C  points under consideration
     * @return  Whether the segment \f$ BC \f$ forms a counter-clockwise turn
     * respect to the segment \f$ AB \f$. Equivalently, whether the vector
     * \f$ \overrightarrow{AC} \f$ lies counter-clockwise with respect to
     * \f$ \overrightarrow{AB} \f$ &mdash; i.e., the angle from the latter
     * to the former is within the open interval \f$ ]-\pi, 0[ \f$ .
     */
    bool isCounterClockwiseTurn(const Point &A, const Point &B, const Point &C);


    /**
     * Equibarycenter of a range of points.
     * @param points  range of points to calculate the barycenter of
     * @return  the equibarycenter of `points`
     *
     * @pre  `points` is not empty (i.e., `points.begin() != points.end()`)
     * @throws error::ValueError if `points` is empty
     */
    Point barycenter(const ConstRange<Point> &points);

    ///@}




    //-------- SEGMENT COMPUTATIONS --------//

    //! @name Segment computations
    //! Utilities for calculations involving segments
    ///@{

    /// Represents a 2D segment delimited by two points.
    struct Segment {
        Point startPt;  ///< segment's start-point
        Point endPt;  ///< segment's end-point

        /// Gets the vector that goes from startPt to endPt
        /// @return the vector `endPt - startPt`
        inline
        Vector2D direction() const { return endPt - startPt; }
    };


    /**
     * A utility class that stores the result of trying to intersect two segments.
     * It stores if the intersection failed --- for example, because the segments
     * are parallel. It can be contextually converted to `bool`.
     */
    class IntersectResult {
    public:
        /**
         * Constructs an intersection result.
         * @param success  whether the intersection succeeded
         * @param intersection  the calculated point of intersection
         */
        IntersectResult(bool success = false, const Point &intersection = {});

        /// @return whether an intersection point was found or not
        explicit inline
        operator bool() const { return success; };

        /**
         * Gets the point of intersection (if one was found)
         * @return the calculated intersection point
         * @pre \link operator bool() `bool(*this)`\endlink is `true`
         */
        const Point &getPoint() const { return point; }

    private:
        Point point;
        bool success;
    };


    /**
     * Computes the intersection of two segments.
     * Note that the computation may fail if the segments are parallel
     * or don't intersect otherwise.
     *
     * @param seg1,seg2  segments to intersect
     * @return  The result of the intersection. If the computation
     * was successful (i.e., the segments intersect at a single point),
     * \link IntersectResult::bool() `bool(result)`\endlink will be true, and
     * \link IntersectResult::getPoint() `result.getPoint()`\endlink will return
     * the intersection point (where `result` is the returned value).
     */
    IntersectResult intersect(const Segment &seg1, const Segment &seg2);


    /**
     * Whether a point is inside a segment.
     * @param P  point under consideration
     * @param seg  segment under consideration
     * @return whether `P` is inside `seg`
     */
    bool isInSegment(const Point &P, const Segment &seg);

    ///@}

}


#endif //CONVEXPOLYGONS_GEOM_H
