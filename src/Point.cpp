//
// Created by Paolo on 07/03/2019.
//

#include "../include/Point.h"


// Returns the vector difference between two points
Vector2D operator-(const Point &A, const Point &B) {
    return {A.x - B.x, A.y - B.y};
}


// Strict weak Point comparison functions
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
    // (if reversed is false; otherwise, vice-versa). In case the angles coincide
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

