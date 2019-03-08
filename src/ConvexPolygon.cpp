#include <algorithm>

#include "../include/ConvexPolygon.h"
#include "../include/utils.h"


// Constructs a convex polygon from a given list of points with a Graham scan
ConvexPolygon::ConvexPolygon(Points &points) {
    const Point P0 = min(points, PointComp::yComp); // Get point with lowest y coordinate
    this->vertices = {P0};
    sort(points.begin(), points.end(), PointComp::angleComp(P0));
}
