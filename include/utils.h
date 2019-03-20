#ifndef CONVEXPOLYGONS_UTILS_H
#define CONVEXPOLYGONS_UTILS_H

#include <vector>
#include <iostream>
#include <sstream>
#include <numeric>
#include "errors.h"


using namespace std;


template<typename T>
vector<T> readVector(istream &is) {
    vector<T> vec;
    T elem;
    while (is >> elem)
        vec.push_back(elem);
    return vec;
}


template<typename T>
void getArgs(istream &argStream, T &first) {
    if (not(argStream >> first))
        throw ValueError("unable to parse arguments");
}


template<typename T, typename ... Types>
void getArgs(istream &argStream, T &first, Types &... slots) {
    getArgs(argStream, first);
    getArgs(argStream, slots...);
}


void prefixPath(string &filePath, const string &prefixPath);

void checkDirectory(const string &dir);


// ---------- extend ----------

template<typename T>
unsigned long _size(const vector<T> &vec) {
    return vec.size();
}

template<typename T, typename ... Types>
unsigned long _size(const vector<T> &vec, const Types & ... others) {
    return vec.size() + _size(others...);
}


template<typename T>
void _extend(vector<T> &destination, const vector<T> &origin) {
    destination.reserve(destination.size() + origin.size());
}

template<typename T, typename ... Types>
void _extend(vector<T> &destination, const vector<T> &first, const Types & ... others) {
    destination.insert(destination.end(), first.begin(), first.end());
    _extend(destination, others...);
}

template<typename T, typename ... Types>
void extend(vector<T> &destination, const vector<T> &first, const Types & ... others) {
    destination.reserve(_size(first, others...));
    _extend(destination, first, others...);
}


#endif //CONVEXPOLYGONS_UTILS_H
