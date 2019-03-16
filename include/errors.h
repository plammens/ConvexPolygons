//
// Created by paolo on 3/14/19.
//

#ifndef CONVEXPOLYGONSS_ERRORS_H
#define CONVEXPOLYGONSS_ERRORS_H

#include <exception>
#include <sstream>


using namespace std;

class Error : public exception {
protected:
    string spec;

public:
    Error(const char *spec = "") : spec(spec) {}
    Error(const string &spec = "") : spec(spec) {}

    const string message() const {
        ostringstream oss(baseMessage(), ios::ate);
        if (not spec.empty()) oss << " (" << spec << ')';
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

class ValueError : public Error {
public:
    ValueError(const string &spec) : Error(spec) {}
    ValueError(const char *spec) : Error(spec) {}

    const char *baseMessage() const override {
        return "invalid argument value";
    }
};


class UndefinedID : public Error {
public:
    UndefinedID(const string &spec) : Error(spec) {}
    UndefinedID(const char *spec) : Error(spec) {}

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

#endif //CONVEXPOLYGONSS_ERRORS_H
