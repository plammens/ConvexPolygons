#include <iostream>
#include "../include/Point.h"

using namespace std;

int main() {
    Point P = {1, 1}, Q = {1, 0.5};
    cout << PointComp::xAngle({0, 0}, true)(P, Q) << endl;
}