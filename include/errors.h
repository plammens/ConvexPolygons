//
// Created by paolo on 3/14/19.
//

#ifndef CONVEXPOLYGONS_ERRORS_H
#define CONVEXPOLYGONS_ERRORS_H

#include <exception>
#include <sstream>


using namespace std;

class CommandError : public exception {
protected:
    string specification;

public:
    CommandError(const char *spec) : specification(spec) {}
    CommandError(const string &spec) : specification(spec) {}

    const string message() const {
        ostringstream oss(baseMessage(), ios::ate);
        oss << " (" << specification << ')';
        return oss.str();
    }

    virtual
    const char *baseMessage() const {
        return "base error";
    };
};


class UnrecognizedCommand : public CommandError {
public:
    UnrecognizedCommand(const string &spec) : CommandError(spec) {}
    UnrecognizedCommand(const char *spec) : CommandError(spec) {}

    const char *baseMessage() const override {
        return "unrecognized command";
    }
};


class SyntaxError : public CommandError {
public:
    SyntaxError(const string &specification) : CommandError(specification) {}
    SyntaxError(const char *specification) : CommandError(specification) {}

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


class IOError : public CommandError {
public:
    IOError(const string &specification) : CommandError(specification) {}
    IOError(const char *specification) : CommandError(specification) {}

    const char *baseMessage() const override {
        return "unable to access file";
    }
};

#endif //CONVEXPOLYGONS_ERRORS_H
