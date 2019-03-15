//
// Created by paolo on 3/14/19.
//

#ifndef CONVEXPOLYGONS_ERRORS_H
#define CONVEXPOLYGONS_ERRORS_H

#include <exception>
#include <sstream>


using namespace std;

class Error : public exception {
protected:
    string spec;

public:
    Error(const char *spec) : spec(spec) {}
    Error(const string &spec) : spec(spec) {}

    const string message() const {
        ostringstream oss(baseMessage(), ios::ate);
        oss << " (" << spec << ')';
        return oss.str();
    }

    virtual
    const char *baseMessage() const {
        return "base error";
    };
};


class UnrecognizedCommand : public Error {
public:
    UnrecognizedCommand(const string &spec) : Error(spec) {}
    UnrecognizedCommand(const char *spec) : Error(spec) {}

    const char *baseMessage() const override {
        return "unrecognized command";
    }
};


class SyntaxError : public Error {
public:
    SyntaxError(const string &spec) : Error(spec) {}
    SyntaxError(const char *spec) : Error(spec) {}

    const char *baseMessage() const override {
        return "wrong syntax";
    }
};


class UndefinedID : public CommandError {
public:
    UndefinedID(const string &specification) : CommandError(specification) {}
    UndefinedID(const char *specification) : CommandError(specification) {}

    const char *baseMessage() const override {
        return "undefined ID";
    }
};


class IOError : public Error {
public:
    IOError(const string &spec) : Error(spec) {}
    IOError(const char *spec) : Error(spec) {}

    const char *baseMessage() const override {
        return "unable to access file";
    }
};

#endif //CONVEXPOLYGONS_ERRORS_H
