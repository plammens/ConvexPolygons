// Interface for 2D vectors

#ifndef CONVEXPOLYGONS_VECTOR2D_H
#define CONVEXPOLYGONS_VECTOR2D_H


// Interface for 2D (geometric) vectors
struct Vector2D {
    double x, y;

    double sqrNorm() const;
    double norm() const;
    bool isNull() const;
};


bool operator==(const Vector2D &u, const Vector2D &rhs);
bool operator!=(const Vector2D &u, const Vector2D &v);

// Some basic arithmetic
Vector2D operator*(double a, const Vector2D &u);
Vector2D operator/(const Vector2D &u, double a);


Vector2D operator+(const Vector2D &u, const Vector2D &v);


double crossProd(const Vector2D & u, const Vector2D& v);


#endif //CONVEXPOLYGONS_VECTOR2D_H
