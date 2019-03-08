#ifndef CONVEXPOLYGON_GEOMETRICVECTOR_H
#define CONVEXPOLYGON_GEOMETRICVECTOR_H

// Interface for 2D (geometric) vectors
class Vector2D {
private:
    double _x, _y;

public:
    Vector2D(double x, double y);

    inline double x() const;
    inline double y() const;
    double sqrNorm() const;
};

#endif //CONVEXPOLYGON_GEOMETRICVECTOR_H
