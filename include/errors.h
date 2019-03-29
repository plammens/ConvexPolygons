// Custom exceptions for the whole project
// (header-only)

#ifndef CONVEXPOLYGONS_ERRORS_H
#define CONVEXPOLYGONS_ERRORS_H

#include <exception>
#include <sstream>


class BaseException : public std::exception {
protected:
    std::string message;

    BaseException() = default;
    BaseException(const std::string &baseMessage, const std::string &specific = "") {
        std::ostringstream oss(baseMessage, std::ios::ate);
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
    UnknownCommand(const std::string &specific = "") : BaseException(base, specific) {}
};


class SyntaxError : public Error {
public:
    static constexpr auto base = "invalid command syntax";
    SyntaxError(const std::string &specific = "") : BaseException(base, specific) {}
};


class ValueError : public Error {
public:
    static constexpr auto base = "invalid value";
    ValueError(const std::string &specific = "") : BaseException(base, specific) {}
};


class UndefinedID : public Error {
public:
    static constexpr auto base = "undefined ID";
    UndefinedID(const std::string &specific = "") : BaseException(base, specific) {}
};


class IOError : public Error {
public:
    static constexpr auto base = "unable to access file";
    IOError(const std::string &specific = "") : BaseException(base, specific) {}
};


// -------------------- Warnings ----------------------


class Warning : public virtual BaseException {};


class UnusedArgument : public Warning {
public:
    static constexpr auto base = "unused argument(s)";
    UnusedArgument(const std::string &specific = "") : BaseException(base, specific) {}
};


#endif //CONVEXPOLYGONS_ERRORS_H
