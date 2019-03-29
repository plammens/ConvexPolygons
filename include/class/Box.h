/** @file
 * Interface for 2D horizontal boxes.
*/

#ifndef CONVEXPOLYGONS_BOX_H
#define CONVEXPOLYGONS_BOX_H

#include "class/Point.h"


//-------- FREE FUNCTIONS --------//

//! @name Free functions
//! Utilities closely related to the Box class.
//!@{

/**
 * Bottom left corner of the box spanned by two points.
 * @param A  first operand
 * @param B  second operand
 * @return \f$ (\min{A_x, B_x}, \min{A_y, B_y}) \f$
 */
Point bottomLeft(const Point &A, const Point &B);

/**
 * Upper right corner of the box spanned by two points.
 * @param A  first operand
 * @param B  second operand
 * @return \f$ (\max{A_x, B_x}, \max{A_y, B_y}) \f$
 */
Point upperRight(const Point &A, const Point &B);

///@}




//-------- BOX CLASS --------//

/**
 * Representation of a horizontal (non-rotated) 2D box. Can be constructed
 * from a pair of points. Each of the four corners can be retrieved individually.
 */
class Box {
public:
    Box(const Point &P, const Point &Q);

    //! @name Getters
    //! Getters for each of the four corners of the box.
    ///@{
    const Point &SW() const { return _SW; } ///< South-West corner (bottom-left)
    const Point &NW() const { return _NW; } ///< North-West corner (upper-left)
    const Point &NE() const { return _NE; } ///< North-East corner (upper-right)
    const Point &SE() const { return _SE; } ///< South-East corner (bottom-right)
    ///@}

private:
    Point _SW, _NW, _NE, _SE;
};


//-------- ASSOCIATED NONMEMBER FUNCTIONS --------//

///@name Equality operators
/// Numerical equality of each of the box's four vertices
///@{

bool operator==(const Box &lhs, const Box &rhs);
bool operator!=(const Box &lhs, const Box &rhs);

///@}


#endif //CONVEXPOLYGONS_BOX_H
