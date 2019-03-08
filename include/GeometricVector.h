#ifndef CONVEXPOLYGON_GEOMETRICVECTOR_H
#define CONVEXPOLYGON_GEOMETRICVECTOR_H

class GeometricVector {
private:
    double _x, _y;

public:
    GeometricVector(double x, double y);

    double x() const;

    double y() const;

    double sqrNorm() const;
};

#endif //CONVEXPOLYGON_GEOMETRICVECTOR_H
