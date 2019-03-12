#ifndef CONVEXPOLYGON_UTILS_H
#define CONVEXPOLYGON_UTILS_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template<typename T>
vector<T> readLineAsVector() {
    vector<T> vec;
    string line;
    getline(cin, line);
    istringstream iss(line);
    T elem;
    while (iss >> elem) vec.push_back(elem);
    return vec;
}

// Returns the sum of binaryOp(x, y) for every consecutive pair x, y in vec
template<typename T, class BinaryOp>
double cyclicSum(const vector<T> &vec, BinaryOp binaryOp) {
    double sum = 0;

    for (auto it = vec.begin(); it < vec.end() - 1; ++it)
        sum += binaryOp(it[0], it[1]);

    // Complete cycle:
    const T &first = vec.front(), &last = vec.back();
    sum += binaryOp(last, first);

    return sum;
}


#endif //CONVEXPOLYGON_UTILS_H
