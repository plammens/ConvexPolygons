/// @file
/// Interface for 2D (geometric) vectors.

#ifndef CONVEXPOLYGONS_VECTOR2D_H
#define CONVEXPOLYGONS_VECTOR2D_H


/**
 * Two-dimensional real vector.
 * Uses cartesian (`x`, `y`) coordinates.
 */
struct Vector2D {
    double x, y;

    /**
     * Squared euclidean norm. This method is used
     * instead of norm() if the square root isn't needed.
     * @return \f$ ||u||^2 \f$, where `u` is the vector
     */
    double squaredNorm() const;

    /**
     * Euclidean norm.
     * @return \f$ ||u|| \f$, where `u` is the vector
     */
    double norm() const;

    /**
     * Numerical nullity test.
     * @return whether `*this` is a null vector
     */
    bool isNull() const;
};



//-------- ASSOCIATED NONMEMBER FUNCTIONS --------//

/// @name Arithmetic operations
///@{

/**
 * Scales the vector by a scalar.
 * @param a  scalar by which to scale the vector
 * @param u  the vector \f$\vec{u}\f$ to be scaled.
 * @return  scaled copy, \f$a\cdot \vec{u}\f$, of the original vector
 */
Vector2D operator*(double a, const Vector2D &u);
Vector2D operator/(const Vector2D &u, double a); ///< Same as operator*(), but for division

/**
 * Component-wise vector sum.
 * @param u,v  vectors to be added together
 * @return the vector \f$\vec{u} + \vec{v}\f$
 */
Vector2D operator+(const Vector2D &u, const Vector2D &v);

///@}



/// @name Equality operators
/// Component-wise numerical equality of vectors.
///@{

bool operator==(const Vector2D &u, const Vector2D &v);
bool operator!=(const Vector2D &u, const Vector2D &v);

///@}


#endif //CONVEXPOLYGONS_VECTOR2D_H
