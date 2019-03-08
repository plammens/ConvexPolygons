//
// Created by Paolo on 07/03/2019.
//

#include "../include/GeometricVector.h"

GeometricVector::GeometricVector(double x, double y) : _x(x), _y(y) {}

inline
double GeometricVector::sqrNorm() const {
    return _x*_x + _y*_y;
}

inline
double GeometricVector::x() const {
    return _x;
}

inline
double GeometricVector::y() const {
    return _y;
}
