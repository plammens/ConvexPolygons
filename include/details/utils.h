// General-purpose utilities
// (header-only)

#ifndef CONVEXPOLYGONS_UTILS_H
#define CONVEXPOLYGONS_UTILS_H

#include <vector>
#include <istream>
#include "errors.h"
#include "consts.h"


using namespace std;

// ------------- numeric ----------

namespace numeric {

    inline
    double scaledEpsilon(double a, double b) {
        return max(1., max(abs(a), abs(b)))*NUM::EPSILON;
    }

    inline
    bool equal(double a, double b) {
        return abs(a - b) < scaledEpsilon(a, b);
    }

    inline
    bool leq(double a, double b) {
        return a < b + scaledEpsilon(a, b);
    }

}


// --------- input reading utils ------------

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

// ----------- File IO utils ----------


inline
int checkDirectory(const string &dir) {
    return system(("mkdir -p " + dir).c_str());
}


inline
void prefixPath(string &filePath, const string &prefixPath) {
    if (checkDirectory(prefixPath) != 0) throw IOError("directory " + prefixPath);
    filePath.insert(0, prefixPath);
}


inline
void checkFileForWriting(const string &filePath) {
    if (not fopen(filePath.c_str(), "w")) throw IOError(filePath);
}



// ---------- extend ----------

template<typename T>
constexpr unsigned long _size(const vector<T> &vec) {
    return vec.size();
}


template<typename T, typename ... Types>
constexpr unsigned long _size(const vector<T> &vec, const Types &... others) {
    return vec.size() + _size(others...);
}


template<typename T, typename ... Types>
void extend(vector<T> &destination, const Types &... vectors) {
    destination.reserve(_size(vectors...));  // reserve copy size beforehand
    _extend(destination, vectors...);
}


template<typename T>
void _extend(vector<T> &destination, const vector<T> &first) {
    destination.insert(destination.end(), first.begin(), first.end());
}


template<typename T, typename ... Types>
void _extend(vector<T> &destination, const vector<T> &first, const Types &... others) {
    destination.insert(destination.end(), first.begin(), first.end());
    _extend(destination, others...);
}


#endif //CONVEXPOLYGONS_UTILS_H
