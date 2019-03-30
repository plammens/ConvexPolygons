/** @file
 * Interface for 2D Points.
*/

#ifndef CONVEXPOLYGONS_POINT_H
#define CONVEXPOLYGONS_POINT_H

#include <istream>
#include "class/Vector2D.h"



/**
 * Two-dimensional point in cartesian coordinates.
 */
struct Point {
    double x;  ///< x coordinate
    double y;  ///< y coordinate
};



//-------- ASSOCIATED NONMEMBER FUNCTIONS --------//

/**
 * Euclidean distance between two points.
 * @param A,B  points under consideration
 * @return the value of `(A - B).norm()`
 */
double distance(const Point &A, const Point &B);



//! @name Arithmetic operations
///@{

/**
 * Vector difference between two points.
 * @param A  end point
 * @param B  start point
 * @return the vector \f$ A - B \f$
 */
Vector2D operator-(const Point &A, const Point &B);

/**
 * Translation of a point by a vector.
 * @param A  start point
 * @param u  translation vector
 * @return the point \f$ A + \vec{u} \f$
 */
Point operator+(const Point &A, const Vector2D& u);

///@}



//! @name Equality operators
//! Numerical component-wise equality test. Compares each component individually with
//! NUM::EPSILON tolerance.
///@{

bool operator==(const Point &A, const Point &B);
bool operator!=(const Point &A, const Point &B);

///@}




//! @name Text IO
//! Formatter and reader functions for Point objects.
///@{

/**
 * Reads space-separated `x`, `y` coordinates into `P`.
 */
std::istream &operator>>(std::istream &is, Point &P);

/**
 * Formats P into space-separated x, y coordinates.
 * Sets the `std::ios_base::fixed` format with 3-digit decimal precision.
 */
std::ostream &operator<<(std::ostream &os, const Point &P);

///@}


#endif
