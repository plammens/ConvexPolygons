#include "../include/Vector2D.h"

// 2D-vector constructor and getters
Vector2D::Vector2D(double x, double y) : _x(x), _y(y) {}

double Vector2D::x() const { return _x; }

double Vector2D::y() const { return _y; }


// Returns the squared euclidean norm
double Vector2D::sqrNorm() const {
    return _x*_x + _y*_y;
}
