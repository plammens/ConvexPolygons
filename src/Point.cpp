//
// Created by Paolo on 07/03/2019.
//

#include "../include/Point.h"

// Point constructor and getters

Point::Point(double x, double y) : _x(x), _y(y) {}

double Point::x() const { return _x; }

double Point::y() const { return _y; }


// Returns the vector difference between two points
GeometricVector Point::operator-(const Point &other) const {
    return GeometricVector(this->_x - other._x, this->_y - other._y);
}


// Strict weak Point comparison functions
namespace PointComp {

    // Returns whether A has a smaller y-coordinate than B
    // (and smaller x-coordinate in case of equality).
    bool yComp(const Point &A, const Point &B) {
        if (A.y() != B.y()) return A.y() < B.y();
        return A.x() < B.x();
    }

    // Constructs a new angle comparison with P as origin
    angleComp::angleComp(const Point &P) : origin(P) {}

    // Compares according to the angles that the lines joining each point
    // to a given origin form with the x-axis. True if first angle is smaller.
    bool angleComp::operator()(const Point &A, const Point &B) {
        GeometricVector u = A - origin, v = B - origin;
        return u.x()*u.x()*u.sqrNorm() > v.x()*v.x()*v.sqrNorm();
    }

}


