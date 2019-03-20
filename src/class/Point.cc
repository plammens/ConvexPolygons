
#include "class/Point.h"
#include "utils.h"


// Returns the vector difference between two points
Vector2D operator-(const Point &A, const Point &B) {
    return {A.x - B.x, A.y - B.y};
}


// Whether vectors AB and AC are in a clockwise configuration (in that order)
bool isClockwiseTurn(const Point &A, const Point &B, const Point &C) {
    Vector2D AB = B - A, AC = C - A;
    return AC.x*AB.y > AB.x*AC.y;  // TODO: refactor cross prod
}


//Equality operators
bool operator==(const Point &A, const Point &B) {
    return numericEquals(A.x, B.x) and numericEquals(A.y, B.y);
}


bool operator!=(const Point &A, const Point &B) { return not(A == B); }


// Strict weak comparison functions for Point
namespace PointComp {

    // Returns whether A has a smaller y-coordinate than B
    // (and smaller x-coordinate in case of equality).
    bool yCoord(const Point &A, const Point &B) {
        if (A.y != B.y) return A.y < B.y;
        return A.x < B.x;
    }


    // Constructs a new xAngle comparison with P as origin. If `reversed` is true,
    // comparison by angle (not the whole ordering) is reversed.
    xAngle::xAngle(const Point &P, bool reversed) : origin(P), reversed(reversed) {}


    // Compares Points according to the angles that the vectors joining the origin
    // with each point form with the x-axis. Returns whether the first angle is smaller
    // (if not reversed; otherwise, vice-versa). In case the angles coincide
    // (or one of them is undefined), returns whether the first vector has smaller norm.
    // Pre: angles are in [0, PI]
    bool xAngle::operator()(const Point &A, const Point &B) {
        Vector2D OA = A - origin, OB = B - origin;
        double normOA = OA.sqrNorm(), normOB = OB.sqrNorm();
        double projA = OA.x*abs(OA.x)*normOB, projB = OB.x*abs(OB.x)*normOA;  // Scaled projections onto the x-axis

        if (projA != projB) return reversed xor (projA > projB);
        else return normOA < normOB;
    }

}


// Euclidean distance
double distance(const Point &A, const Point &B) {
    return (A - B).norm();
}


Point bottomLeft(const Point &A, const Point &B) {
    return {min(A.x, B.x), min(A.y, B.y)};
}


Point upperRight(const Point &A, const Point &B) {
    return {max(A.x, B.x), max(A.y, B.y)};
}


Point operator+(const Point &A, const Vector2D &u) {
    return {A.x + u.x, A.y + u.y};
}


Point barycenter(Points::const_iterator begin, Points::const_iterator end) {
    if (begin == end) throw ValueError("no points given for barycenter");
    // Here we calculate the "average" of the points seen as vectors.
    // We use a custom binary operator that converts `Point`s to `Vector2D`s along the way.
    Vector2D sumVector = accumulate(begin, end, Vector2D{0, 0},
                                    [](const Vector2D &u, const Point &P) {
                                        return u + (const Vector2D &)(P);
                                    });
    return Point{0, 0} + sumVector/(end - begin);
}


// Extraction operation from an input stream into a point
istream &operator>>(istream &is, Point &P) {
    return (is >> P.x >> P.y);
}


ostream &operator<<(ostream &os, const Point &P) {
    os.setf(ios::fixed);
    os.precision(3);
    return os << P.x << ' ' << P.y;
}
