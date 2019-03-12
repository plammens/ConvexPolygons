#include <cmath>
#include "../include/Vector2D.h"


// Returns the squared euclidean norm
double Vector2D::sqrNorm() const {
    return x*x + y*y;
}

double Vector2D::norm() const {
    return sqrt(sqrNorm());
}
