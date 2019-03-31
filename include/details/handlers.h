/// @file
/// Command handlers that handle user input and dispatch to the appropriate function.
/// Alongside other input-output handling facilities.

#ifndef CONVEXPOLYGONS_HANDLERS_H
#define CONVEXPOLYGONS_HANDLERS_H

#include <functional> // std::function
#include <istream>
#include <map>
#include <string>
#include "consts.h"
#include "polygonmap.h"


/** @name Command handlers
 *
 * Routines that handle user-issued commands and dispatch to the appropriate function.
 * They all share the same signature:
 * \code{.cpp}
 * handlerName(const std::string &keyword, std::istream &argStream, PolygonMap &polygonMap);
 * \endcode
 *
 * @param keyword  command keyword
 * @param argStream  input stream of arguments to the command
 * @param polygonMap  map of polygons with which to execute the command
 *
 * @exceptions Any exception thrown by executing the command or parsing the arguments.
 * Most common exceptions are:
 *  - error::UndefinedID
 *  - error::ValueError
 *  - error::SyntaxError
 */
///@{

/// Command handler signature
typedef std::function<void(const std::string &, std::istream &, PolygonMap &)> CommandHandler;


/// Subroutine to handle creation/assignment of a single polygon
void handleIDManagement(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);

/// Subroutine to handle commands involving printing info about a single polygon
void handlePolygonMethod(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);

/// Subroutine to handle binary operations with polygons
void handleBinaryOperation(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);

/// Subroutine to handle n-ary operations with polygons
void handleNAryOperation(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);

/// Subroutine to handle file-related commands
void handleIOCommand(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);

/// Subroutine to run commands that take no arguments
void handleNullaryCommand(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);


///@}



//-------- COMMAND HANDLER MAP --------//

/// Maps each command keyword to its corresponding command handler
const std::map<std::string, CommandHandler> cmdHandlerMap = {
        {cmd::POLYGON,      handleIDManagement},
        {cmd::DELETE,       handleIDManagement},
        {cmd::PRINT,        handlePolygonMethod},
        {cmd::PRETTYPRINT,  handlePolygonMethod},
        {cmd::AREA,         handlePolygonMethod},
        {cmd::PERIMETER,    handlePolygonMethod},
        {cmd::VERTICES,     handlePolygonMethod},
        {cmd::CENTROID,     handlePolygonMethod},
        {cmd::SETCOL,       handlePolygonMethod},
        {cmd::INTERSECTION, handleBinaryOperation},
        {cmd::UNION,        handleBinaryOperation},
        {cmd::INSIDE,       handleBinaryOperation},
        {cmd::BBOX,         handleNAryOperation},
        {cmd::LIST,         handleNullaryCommand},
        {cmd::SAVE,         handleIOCommand},
        {cmd::LOAD,         handleIOCommand},
        {cmd::DRAW,         handleIOCommand},
        {cmd::PAINT,        handleIOCommand}
};

/**
 * Gets the command handler associated to a keyword.
 * @param keyword  command keyword
 * @return the command handler corresponding to `keyword`
 *
 * @pre `keyword` is in ::cmdHandlerMap (i.e., it is recognized)
 * @throws error::UnknownCommand if `keyword` isn't recognized as
 * a valid command keyword
 */
CommandHandler getCommandHandler(const std::string &keyword);



//-------- COMMAND PARSING --------//

/**
 * Parses a complete command (as a string). Commands correspond to an entire
 * line of user input. Catches any exception that inherits from error::Error
 * or error::Warning.
 *
 * @param[in] command  full command (keyword + arguments) issued by the user
 * @param[in, out] polygonMap  polygon map in which the operations are to be performed
 */
void parseCommand(const std::string &command, PolygonMap &polygonMap);


#endif //CONVEXPOLYGONS_HANDLERS_H
