#include <cmath>
#include "class/Vector2D.h"


// Returns the squared euclidean norm
double Vector2D::sqrNorm() const {
    return x*x + y*y;
}

// Euclidean norm
double Vector2D::norm() const {
    return sqrt(sqrNorm());
}
