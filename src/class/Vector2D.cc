#include "class/Vector2D.h"

#include <cmath>  // std::sqrt
#include "details/numeric.h"



//-------- MEMBER FUNCTIONS --------//

double Vector2D::squaredNorm() const {
    return x*x + y*y;
}

double Vector2D::norm() const {
    return sqrt(squaredNorm());
}

bool Vector2D::isNull() const {
    return numeric::equal(x, 0) and numeric::equal(y, 0);
}




//-------- ASSOCIATED NONMEMBER FUNCTIONS --------//

//---- Arithmetic operations ----//

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


//---- Equality operators ----//

bool operator==(const Vector2D &u, const Vector2D &v) {
    return numeric::equal(u.x, v.x) and numeric::equal(u.y, v.y);
}

bool operator!=(const Vector2D &u, const Vector2D &v) {
    return not(v == u);
}
