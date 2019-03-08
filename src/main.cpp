#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/Point.h"
#include "../include/ConvexPolygon.h"

using namespace std;

int main() {
    Points points = {{0, 1},
                     {0, 2},
                     {0, 0},
                     {1, 1}};
    const Point P0 = *min_element(points.begin(), points.end(), PointComp::yCoord);
    cout << P0.x << ' ' << P0.y << '\n' << endl;
    sort(points.begin(), points.end(), PointComp::xAngle(P0, true));
    for_each(points.begin(), points.end(), [](const Point &P) { cout << P.x << ' ' << P.y << endl; });
}