#include "../include/Point.h"


// Returns the vector difference between two points
Vector2D operator-(const Point &A, const Point &B) {
    return {A.x - B.x, A.y - B.y};
}

// Whether vectors AB and AC are in a clockwise configuration (in that order)
bool isClockwiseTurn(const Point &A, const Point &B, const Point &C) {
    Vector2D AB = B - A, AC = C - A;
    return AC.x*AB.y > AB.x*AC.y;
}

//Equality operators
bool operator==(const Point &A, const Point &B) { return A.x == B.x and A.y == B.y; }
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
        double normA = OA.sqrNorm(), normB = OB.sqrNorm();
        double projA = OA.x*OA.x*normB, projB = OB.x*OB.x*normA;  // Scaled projections onto the x-axis

        if (projA != projB) return (not reversed ? projA > projB : projA < projB);
        else return normA < normB;
    }

}

// Extraction operation from an input stream into a point
istream &operator>>(istream &is, Point &P) {
    return (is >> P.x >> P.y);
}

// Euclidean distance
double distance(const Point &A, const Point &B) {
    return (A - B).norm();
}

