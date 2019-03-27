#include "class/Point.h"

#include <numeric>  // std::accumulate
#include "details/range.h" // Range<T>
#include "details/utils.h"


// Returns the vector difference between two points
Vector2D operator-(const Point &A, const Point &B) {
    return {A.x - B.x, A.y - B.y};
}


// Whether vectors AB and AC are in a clockwise configuration (in that order)
bool isClockwiseTurn(const Point &A, const Point &B, const Point &C) {
    Vector2D AB = B - A, AC = C - A;
    return crossProd(AB, AC) < 0;
}

// Whether vectors AB and AC are in a clockwise configuration (in that order)
bool isCounterClockwiseTurn(const Point &A, const Point &B, const Point &C) {
    Vector2D AB = B - A, AC = C - A;
    return crossProd(AB, AC) > 0;
}


//Equality operators
bool operator==(const Point &A, const Point &B) {
    return numeric::equal(A.x, B.x) and numeric::equal(A.y, B.y);
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


    // Constructs a new xAngle comparison with P as origin. If `descending` is true,
    // comparison by angle (not the whole ordering) is descending.
    xAngle::xAngle(const Point &P, bool descending) : origin(P), reversed(descending) {}


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


Point operator+(const Point &A, const Vector2D &u) {
    return {A.x + u.x, A.y + u.y};
}


Point barycenter(ConstRange <Point> points) {
    if (points.empty()) throw ValueError("no points given for barycenter");
    // Here we calculate the "average" of the points seen as vectors.
    // We use a custom binary operator that converts `Point`s to `Vector2D`s along the way.
    Vector2D sumVector = accumulate(points.begin(), points.end(), Vector2D{0, 0},
                                    [](const Vector2D &u, const Point &P) {
                                        return u + (const Vector2D &)(P);
                                    });
    return Point{0, 0} + sumVector/boost::size(points);
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
