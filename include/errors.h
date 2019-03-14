//
// Created by paolo on 3/14/19.
//

#ifndef CONVEXPOLYGONS_ERRORS_H
#define CONVEXPOLYGONS_ERRORS_H

#include <exception>

using namespace std;

class UnrecognizedCommand : exception {};

class SyntaxError : exception {};

class UndefinedID : exception {};

class IOError : exception {};

#endif //CONVEXPOLYGONS_ERRORS_H
