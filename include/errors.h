//
// Created by paolo on 3/14/19.
//

#ifndef CONVEXPOLYGONS_ERRORS_H
#define CONVEXPOLYGONS_ERRORS_H

#include <exception>

using namespace std;

class IOError : exception {};

class SyntaxError : exception {};

class UnrecognizedCommand : exception {};

#endif //CONVEXPOLYGONS_ERRORS_H
