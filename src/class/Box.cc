/** @file
 * Implementation of Box's interface.
*/


#include "class/Box.h"


////////// CLASS FUNCTIONS //////////

Box::Box(const Point &P, const Point &Q) : _SW(bottomLeft(P, Q)), _NE(upperRight(P, Q)) {
    _NW = {_SW.x, _NE.y};  // north-west
    _SE = {_NE.x, _SW.y};  // south-east
}



////////// ASSOCIATED NONMEMBER FUNCTIONS //////////

Point bottomLeft(const Point &A, const Point &B) {
    return {std::min(A.x, B.x), std::min(A.y, B.y)};
}


Point upperRight(const Point &A, const Point &B) {
    return {std::max(A.x, B.x), std::max(A.y, B.y)};
}



////////// EQUALITY OPERATORS //////////

bool operator==(const Box &lhs, const Box &rhs) {
    return lhs.SW() == rhs.SW() and lhs.NE() == rhs.NE();
}


bool operator!=(const Box &lhs, const Box &rhs) {
    return not(rhs == lhs);
}
