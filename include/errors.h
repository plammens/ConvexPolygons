/**
 * @file
 * Custom exceptions for the whole project. Exceptions are grouped into
 * errors and warnings, both of which inherit from a custom base exception.
 */

#ifndef CONVEXPOLYGONS_ERRORS_H
#define CONVEXPOLYGONS_ERRORS_H

#include <exception>
#include <sstream>


//-------- BASE EXCEPTION --------//

/**
 * Base class for all custom exceptions. Stores a message as a string.
 * Instances can only be constructed from within a child class,
 * since the constructors are protected.
 */
class BaseException : public std::exception {
protected:
    std::string message;  ///< message to be returned by what()

    BaseException() = default;

    /**
     * Construct a new exception from a base message and optional additional details.
     * The base message is intended to be class-specific, while the additional
     * details string is intended to be instance-specific.
     *
     * @param baseMessage  generic message for the kind of exception being created
     * @param details  additional information as to why the exception was thrown
     */
    BaseException(const std::string &baseMessage, const std::string &details = "") {
        std::ostringstream oss(baseMessage, std::ios::ate);
        if (not details.empty()) oss << " (" << details << ')';
        message = oss.str();
    }

public:
    /// `std::exception`-compliant message getter
    const char *what() const noexcept override {
        return message.c_str();
    }
};



//-------- ERRORS --------//

/// virtual base class from which all errors inherit
class Error : public virtual BaseException {};


/// Indicates that a command whose keyword is unknown was issued
class UnknownCommand : public Error {
public:
    static constexpr auto base = "unrecognized command";
    UnknownCommand(const std::string &specific = "") : BaseException(base, specific) {}
};


/// Indicates that a certain command was issued with an invalid syntax
class SyntaxError : public Error {
public:
    static constexpr auto base = "invalid command syntax";
    SyntaxError(const std::string &specific = "") : BaseException(base, specific) {}
};


/// Indicates that an algorithm encountered a situation in which it is not well-defined;
/// i.e., a value that doesn't meet a function's prerequisites was passed.
class ValueError : public Error {
public:
    static constexpr auto base = "invalid value";
    ValueError(const std::string &specific = "") : BaseException(base, specific) {}
};


/// Indicates that a certain polygon ID doesn't yet exist
class UndefinedID : public Error {
public:
    static constexpr auto base = "undefined ID";
    UndefinedID(const std::string &specific = "") : BaseException(base, specific) {}
};


/// Indicates an error in reading or writing to a file
class IOError : public Error {
public:
    static constexpr auto base = "unable to access file";
    IOError(const std::string &specific = "") : BaseException(base, specific) {}
};




//-------- WARNINGS --------//

/// virtual base class from which all warnings inherit
class Warning : public virtual BaseException {};


/// Indicates that an unused argument was detected when parsing a command
class UnusedArgument : public Warning {
public:
    static constexpr auto base = "unused argument(s)";
    UnusedArgument(const std::string &specific = "") : BaseException(base, specific) {}
};


#endif //CONVEXPOLYGONS_ERRORS_H
