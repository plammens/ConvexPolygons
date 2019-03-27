#include "class/Vector2D.h"

#include <cmath>  // std::sqrt
#include "details/utils.h"


// Returns the squared euclidean norm
double Vector2D::sqrNorm() const {
    return x*x + y*y;
}


// Euclidean norm
double Vector2D::norm() const {
    return sqrt(sqrNorm());
}


bool Vector2D::isNull() const {
    return numeric::equal(x, 0) and numeric::equal(y, 0);
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


double crossProd(const Vector2D &u, const Vector2D &v) {
    return u.x*v.y - u.y*v.x;
}


bool operator==(const Vector2D &u, const Vector2D &rhs) {
    return numeric::equal(u.x, rhs.x) and numeric::equal(u.y, rhs.y);
}


bool operator!=(const Vector2D &u, const Vector2D &v) {
    return not(v == u);
}
