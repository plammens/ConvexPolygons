/// @file
/// Geometric utilities of various sorts

#ifndef CONVEXPOLYGONS_GEOM_H
#define CONVEXPOLYGONS_GEOM_H

#include "class/Point.h"
#include "details/range.h"


/// Namespace for geometric utilities of various sorts
namespace geom {

    /// Represents a 2D segment delimited by two points.
    struct Segment {
        Point startPt;  ///< segment's start-point
        Point endPt;  ///< segment's end-point

        /// Gets the vector that goes from startPt to endPt
        /// @return the vector `endPt - startPt`
        Vector2D direction() const;
    };


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
         * @pre \link operator bool() `bool(*this)` \endlink is `true`
         */
        const Point &getPoint() const { return point; }

    private:
        Point point;
        bool success;
    };


    IntersectResult intersect(const Segment &seg1, const Segment &seg2);

    bool isInSegment(const Point &P, const Segment &r);


// Returns whether the vector AC lies clockwise with respect to AB
    bool isClockwiseTurn(const Point &A, const Point &B, const Point &C);
    bool isCounterClockwiseTurn(const Point &A, const Point &B, const Point &C);

// Barycenter of a range of points
    Point barycenter(ConstRange <Point> points);

    namespace PointComp {
        bool xCoord(const Point &A, const Point &B);

        struct yAngle {
            Point origin;

            explicit yAngle(const Point &P);
            bool operator()(const Point &A, const Point &B);
        };
    }

}


#endif //CONVEXPOLYGONS_GEOM_H
