// Some text formatting utilities for test/debug output

#ifndef CONVEXPOLYGONS_TEST_CONFIG_H
#define CONVEXPOLYGONS_TEST_CONFIG_H

#include <iostream>
#include "class/ConvexPolygon.h"


template<typename T>
ostream &operator<<(ostream &os, const std::vector<T> &vec) {
    os << '{';
    auto it = vec.begin();
    if (not vec.empty()) os << *it;
    for (++it; it < vec.end(); ++it)
        os << ", " << *it;
    os << '}';
    return os;
}


inline
ostream &operator<<(ostream &os, const ConvexPolygon &pol) {
    return os << pol.getVertices();
}


#endif //CONVEXPOLYGONS_TEST_CONFIG_H
