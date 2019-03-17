#include <cmath>
#include <class/Vector2D.h>


// Returns the squared euclidean norm
double Vector2D::sqrNorm() const {
    return x*x + y*y;
}

// Euclidean norm
double Vector2D::norm() const {
    return sqrt(sqrNorm());
}

Vector2D operator*(double a, const Vector2D &u) {
    return {a*u.x, a*u.y};
}

Vector2D operator/(const Vector2D &u, double a) {
    return (1/a)*u;
}

Vector2D operator+(const Vector2D &u, const Vector2D &v) {
    return {u.x + v.x, u.y + v.y};
}