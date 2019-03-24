#include "class/Box.h"


Box::Box(const Point &P, const Point &Q) : _SW(bottomLeft(P, Q)), _NE(upperRight(P, Q)) {
    _NW = {_SW.x, _NE.y};  // north-west
    _SE = {_NE.x, _SW.y};  // south-east
}


bool operator==(const Box &lhs, const Box &rhs) {
    return lhs.SW() == rhs.SW() and lhs.NE() == rhs.NE();
}


bool operator!=(const Box &lhs, const Box &rhs) {
    return not(rhs == lhs);
}


Point bottomLeft(const Point &A, const Point &B) {
    return {min(A.x, B.x), min(A.y, B.y)};
}


Point upperRight(const Point &A, const Point &B) {
    return {max(A.x, B.x), max(A.y, B.y)};
}
