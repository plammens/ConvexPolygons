#include <algorithm>

#include "../include/ConvexPolygon.h"

using namespace std;


// Constructs a convex polygon from a given list of points with a Graham scan
ConvexPolygon::ConvexPolygon(Points &points) {
    // Get point with lowest y coordinate:
    const Point P0 = *min_element(points.begin(), points.end(), PointComp::yCoord);

    // Sort the points in increasing order of the angle they form with x-axis (relative to P0)
    sort(points.begin(), points.end(), PointComp::xAngle(P0, true));
}
