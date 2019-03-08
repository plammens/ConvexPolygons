#ifndef CONVEXPOLYGON_CONVEXPOLYGON_H
#define CONVEXPOLYGON_CONVEXPOLYGON_H

#include <vector>
#include <string>

#include "Point.h"

using namespace std;


typedef vector<Point> Points;


class ConvexPolygon {
private:
    Points vertices;
    string ID;

public:
    ConvexPolygon(Points &points);

    unsigned long vertexCount() const;

    void print() const;
};


#endif //CONVEXPOLYGON_CONVEXPOLYGON_H
