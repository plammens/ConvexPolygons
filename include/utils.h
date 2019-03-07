//
// Created by Paolo on 07/03/2019.
//

#ifndef CONVEXPOLYGON_UTILS_H
#define CONVEXPOLYGON_UTILS_H

#include <vector>
#include <functional>
#include <cassert>

using namespace std;

// Returns the minimal element of a vector according to a certain comparison
template<typename T, class Comp>
T min(const vector<T> &vec, Comp comp) {
    assert(not vec.empty());
    T currentMin = vec[0];
    for (const T &elem : vec) currentMin = min(currentMin, elem, comp);
    return currentMin;
}

// Returns the minimal element of a vector according to std::less<T>
template<typename T>
T min(const vector<T> &vec) {
    return min(vec, less<T>());
}

#endif //CONVEXPOLYGON_UTILS_H
