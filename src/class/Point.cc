#include "class/Point.h"

#include "details/range.h" // Range<T>
#include "details/numeric.h"


//-------- ASSOCIATED NONMEMBER FUNCTIONS --------//


double distance(const Point &A, const Point &B) {
    return (A - B).norm();
}


//---- Arithmetic operations ----//

// Returns the vector difference between two points
Vector2D operator-(const Point &A, const Point &B) {
    return {A.x - B.x, A.y - B.y};
}

Point operator+(const Point &A, const Vector2D &u) {
    return {A.x + u.x, A.y + u.y};
}


//---- Equality operators ----//

bool operator==(const Point &A, const Point &B) {
    return numeric::equal(A.x, B.x) and numeric::equal(A.y, B.y);
}

bool operator!=(const Point &A, const Point &B) { return not(A == B); }



//---- Text io ----//

// Extraction operation from an input stream into a point
std::istream &operator>>(std::istream &is, Point &P) {
    return (is >> P.x >> P.y);
}

std::ostream &operator<<(std::ostream &os, const Point &P) {
    os.setf(std::ios::fixed);
    os.precision(3);
    return os << P.x << ' ' << P.y;
}
