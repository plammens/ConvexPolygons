#ifndef CONVEXPOLYGON_CONVEXPOLYGON_H
#define CONVEXPOLYGON_CONVEXPOLYGON_H

#include <vector>
#include <string>

#include "class/Point.h"
#include "class/RGBColor.h"


using namespace std;


typedef vector<Point> Points;


class ConvexPolygon {
private:
    Points vertices;
    string ID;
    RGBColor color;

public:
    ConvexPolygon() = default;
    ConvexPolygon(const string &ID, Points &points);

    unsigned long vertexCount() const;
    double area() const;
    double perimeter() const;
    
    void setcol(double r, double g, double b);

    void print() const;
    friend ostream& operator<<(ostream&, const ConvexPolygon&);
};


#endif //CONVEXPOLYGON_CONVEXPOLYGON_H
