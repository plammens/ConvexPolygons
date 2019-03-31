/// @file
/// Inline functions for numerical comparisons (header-only)

#ifndef CONVEXPOLYGONS_NUMERIC_H
#define CONVEXPOLYGONS_NUMERIC_H

#include <cmath>
#include "consts.h"


namespace numeric {

    inline
    bool equal(double a, double b) {
        return std::abs(a - b) < numeric::EPSILON;
    }

    inline
    bool leq(double a, double b) {
        return a < b + numeric::EPSILON;
    }

    inline
    bool geq(double a, double b) {
        return leq(b, a);
    }

    inline
    bool less(double a, double b) {
        return not leq(b, a);
    }

    inline
    bool greater(double a, double b) {
        return less(b, a);
    }

}



#endif //CONVEXPOLYGONS_NUMERIC_H
