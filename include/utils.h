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


#endif //CONVEXPOLYGONS_UTILS_H
