// Interface for 2D points

#ifndef CONVEXPOLYGON_POINT_H
#define CONVEXPOLYGON_POINT_H


class Point {
private:
    double x, y;

public:
    Point(double x, double y);

    static
    bool yComp(const Point &A, const Point &B);
};


#endif //CONVEXPOLYGON_POINT_H
