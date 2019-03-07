#ifndef CONVEXPOLYGON_CONVEXPOLYGON_H
#define CONVEXPOLYGON_CONVEXPOLYGON_H

#include <vector>
#include "Point.h"

using namespace std;


typedef vector<Point> Points;

class ConvexPolygon {
private:
    Points vertices;
    unsigned vertexCount = 0;
    unsigned edgeCount = 0;

public:
    ConvexPolygon(Points P);

};


#endif //CONVEXPOLYGON_CONVEXPOLYGON_H
