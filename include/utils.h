#ifndef CONVEXPOLYGON_UTILS_H
#define CONVEXPOLYGON_UTILS_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template<typename T>
vector<T> readLineAsVec() {
    vector<T> vec;
    string line;
    getline(cin, line);
    istringstream iss(line);
    T elem;
    while (iss >> elem) vec.push_back(elem);
    return vec;
}


#endif //CONVEXPOLYGON_UTILS_H
