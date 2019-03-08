#ifndef CONVEXPOLYGON_GEOMETRICVECTOR_H
#define CONVEXPOLYGON_GEOMETRICVECTOR_H

// Interface for 2D (geometric) vectors
struct Vector2D {
    double x, y;

    double sqrNorm() const;
};

#endif //CONVEXPOLYGON_GEOMETRICVECTOR_H
