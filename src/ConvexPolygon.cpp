#include <algorithm>
#include <iostream>

#include "../include/ConvexPolygon.h"

using namespace std;


// Constructs a convex polygon from a given list of points with a Graham scan
ConvexPolygon::ConvexPolygon(Points &points) {
    if (points.empty()) return;

    // Get point with lowest y coordinate:
    const Point P0 = *min_element(points.begin(), points.end(), PointComp::yCoord);
    // Sort the points in increasing order of the angle they form with x-axis (relative to P0):
    sort(points.begin(), points.end(), PointComp::xAngle(P0, true));

    vertices.push_back(P0);
    if (points.size() > 1 and points[1] != P0) vertices.push_back(points[1]);

    for (auto it = points.begin() + 2; it < points.end(); ++it) {
        while (vertices.size() >= 2 and not isClockwiseTurn(vertices.end()[-2], vertices.end()[-1], *it))
            vertices.pop_back();
        vertices.push_back(*it);
    }
}

unsigned long ConvexPolygon::vertexCount() const {
    return vertices.size();
}

void ConvexPolygon::print() const {
    cout << ID;
    for (const Point &P : vertices)
        cout << ' ' << P.x << ' ' << P.y;
    cout << endl;
}
