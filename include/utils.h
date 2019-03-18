#ifndef CONVEXPOLYGONS_UTILS_H
#define CONVEXPOLYGONS_UTILS_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <numeric>
#include "errors.h"


using namespace std;

template<typename Iter>
using ValueT = typename iterator_traits<Iter>::value_type;


template<typename T>
vector<T> readVector(istream &is) {
    vector<T> vec;
    T elem;
    while (is >> elem) vec.push_back(elem);
    return vec;
}


// Base case
void format(string::const_iterator &it, const string::const_iterator &end, ostream &os);

// Recursive variadic template
template<typename T, typename ... Types>
void format(string::const_iterator &it, const string::const_iterator &end,
            ostream &os, T first, Types ... args) {

    for (; it < end and *it != '%'; ++it) os << *it;
    if (it < end) {
        os << first;
        format(++it, end, os, args...);
    }
}

// User interface
template<typename ... Types>
string format(const string &pattern, Types ... args) {
    ostringstream oss;
    auto it = pattern.cbegin(), end = pattern.cend();
    format(it, end, oss, args...);
    return oss.str();
}

// TODO: use boost?


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


// Average of a vector whose type supports operator+ and operator/
template<typename R, class InputIt, class BinaryOp>
R average(InputIt first, InputIt last, BinaryOp op) {
    return accumulate(first, last, R{}, op)/distance(first, last);
}

template<class InputIt>
ValueT<InputIt> average(InputIt first, InputIt last) {
    return average(first, last, plus<ValueT<InputIt>>());
}


void prefixPath(string &filePath, const string &prefixPath);

void checkDirectory(const string &dir);

#endif //CONVEXPOLYGONS_UTILS_H
