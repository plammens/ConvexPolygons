//
// Created by Paolo on 07/03/2019.
//

#include "../include/Point.h"

// Point constructor and getters

Point::Point(double x, double y) : _x(x), _y(y) {}

double Point::x() const { return _x; }

double Point::y() const { return _y; }


// Returns the vector difference between two points
Vector2D Point::operator-(const Point &other) const {
    return Vector2D(this->_x - other._x, this->_y - other._y);
}


// Strict weak Point comparison functions
namespace PointComp {

    // Returns whether A has a smaller y-coordinate than B
    // (and smaller x-coordinate in case of equality).
    bool yCoord(const Point &A, const Point &B) {
        if (A.y() != B.y()) return A.y() < B.y();
        return A.x() < B.x();
    }

    // Constructs a new xAngle comparison with P as origin. If `reversed` is true,
    // comparison is reversed.
    xAngle::xAngle(const Point &P, bool reversed) : origin(P), reversed(reversed) {}

    // Compares according to the angles that the lines joining each point
    // to a given origin form with the x-axis. If `reversed` is `false, returns
    // true if first xAngle is smaller, and vice-versa.
    // Pre: angles are in [0, PI]
    bool xAngle::operator()(const Point &A, const Point &B) {
        Vector2D OA = A - origin, OB = B - origin;
        double projA, projB;  // Scaled projections onto the x-axis
        projA = OA.x()*OA.x()*OB.sqrNorm();
        projB = OB.x()*OB.x()*OA.sqrNorm();
        return (not reversed ? projA > projB : projA < projB);
    }

}

