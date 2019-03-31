/// @file
/// General-purpose utilities (header-only)

#ifndef CONVEXPOLYGONS_UTILS_H
#define CONVEXPOLYGONS_UTILS_H

#include <vector>
#include <istream>
#include "errors.h"
#include "consts.h"



//-------- INPUT READING --------//

/**
 * Reads a sequence of objects of homogeneous type and creates
 * a vector out of it.
 *
 * @tparam T  type of objects to read
 * @param is  input stream
 * @return a vector with all of the read objects
 */
template<typename T>
std::vector<T> readVector(std::istream &is) {
    std::vector<T> vec;
    T elem;
    while (is >> elem)
        vec.push_back(elem);
    return vec;
}


/// Base case of the recursive variadic template getArgs()
template<typename T>
void getArgs(std::istream &argStream, T &first) {
    if (not(argStream >> first))
        throw error::ValueError("unable to parse arguments");
}


/**
 * Variadic template that reads values from an input stream
 * into each of its arguments.
 *
 * @param[in] argStream  input stream from which to get values
 * @param[out] first  first object to write input into
 * @param[out] slots  references to objects to write input into
 *
 * @pre `argStream` contains valid literals for each of the requested
 * types
 * @throws error::ValueError if a literal for one of the objects is
 * invalid
 */
template<typename T, typename ... Types>
void getArgs(std::istream &argStream, T &first, Types &... slots) {
    getArgs(argStream, first);
    getArgs(argStream, slots...);
}


// ----------- File io utils ----------


/**
 * Prefixes a file path with another path.
 * @param[out] filePath  file path
 * @param prefixPath  path with which to prefix `filePath`
 */
inline
void prefixPath(std::string &filePath, const std::string &prefixPath) {
    if (prefixPath.empty()) return;

    std::string prefix = prefixPath;
    if (prefix.back() != '/') prefix.push_back('/');
    filePath.insert(0, prefix);
}


/**
 * Checks that a file path is valid and can be written to.
 * @param filePath  file path
 */
inline
void checkFileForWriting(const std::string &filePath) {
    if (not fopen(filePath.c_str(), "w")) throw error::IOError(filePath);
}



//-------- EXTEND --------//

// Variadic template to get the total size of an arbitrary number of vectors (internal use)
template<typename T, typename ... Types>
constexpr unsigned long _size(const std::vector<T> &vec, const Types &... others) {
    return vec.size() + _size(others...);
}

// Base case for _size()
template<typename T>
constexpr unsigned long _size(const std::vector<T> &vec) {
    return vec.size();
}


/**
 * Recursive variadic template to extend a vector with the contents of
 * an arbitrary number of vectors.
 * @param[out] destination  vector to be extended
 * @param[in] vectors  vectors to copy data from
 */
template<typename T, typename ... Types>
void extend(std::vector<T> &destination, const Types &... vectors) {
    destination.reserve(_size(vectors...));  // reserve copy size beforehand
    _extend(destination, vectors...);
}


// Base case for _extend()
template<typename T>
void _extend(std::vector<T> &destination, const std::vector<T> &first) {
    destination.insert(destination.end(), first.begin(), first.end());
}


// Internal version of extend()
template<typename T, typename ... Types>
void _extend(std::vector<T> &destination, const std::vector<T> &first, const Types &... others) {
    destination.insert(destination.end(), first.begin(), first.end());
    _extend(destination, others...);
}


#endif //CONVEXPOLYGONS_UTILS_H
