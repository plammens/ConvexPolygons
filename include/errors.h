// Custom exceptions for the whole project
// (header-only)

#ifndef CONVEXPOLYGONS_ERRORS_H
#define CONVEXPOLYGONS_ERRORS_H

#include <exception>
#include <sstream>


using namespace std;


class BaseException : public exception {
protected:
    string message;

    BaseException() = default;
    BaseException(const string &baseMessage, const string &specific = "") {
        ostringstream oss(baseMessage, ios::ate);
        if (not specific.empty()) oss << " (" << specific << ')';
        message = oss.str();
    }

public:
    const char *what() const noexcept override {
        return message.c_str();
    }
};

// ---------------- Errors -----------------------

class Error : public virtual BaseException {};


class UnknownCommand : public Error {
public:
    static constexpr auto base = "unrecognized command";
    UnknownCommand(const string &specific = "") : BaseException(base, specific) {}
};


class SyntaxError : public Error {
public:
    static constexpr auto base = "invalid command syntax";
    SyntaxError(const string &specific = "") : BaseException(base, specific) {}
};


class ValueError : public Error {
public:
    static constexpr auto base = "invalid value";
    ValueError(const string &specific = "") : BaseException(base, specific) {}
};


class UndefinedID : public Error {
public:
    static constexpr auto base = "undefined ID";
    UndefinedID(const string &specific = "") : BaseException(base, specific) {}
};


class IOError : public Error {
public:
    static constexpr auto base = "unable to access file";
    IOError(const string &specific = "") : BaseException(base, specific) {}
};


// -------------------- Warnings ----------------------


class Warning : public virtual BaseException {};


class UnusedArgument : public Warning {
public:
    static constexpr auto base = "unused argument(s)";
    UnusedArgument(const string &specific = "") : BaseException(base, specific) {}
};


#endif //CONVEXPOLYGONS_ERRORS_H
