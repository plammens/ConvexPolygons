// Command handlers that handle user input and dispatch to the appropriate function

#ifndef CONVEXPOLYGONS_HANDLERS_H
#define CONVEXPOLYGONS_HANDLERS_H

#include <functional> // function
#include <iostream>
#include <map>
#include <string>
#include "consts.h"
#include "polygonmap.h"

// Command handler signature
typedef std::function<void(const std::string &, std::istream &, PolygonMap &)> CommandHandler;


// ---------------------------------------------------------------


// non-const version

// Subroutine to handle creation/assignment of a single polygon
void handleIDManagement(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);

// Subroutine to handle commands involving printing info about a single polygon
void handlePolygonMethod(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);

// Subroutine to handle operations with polygons
void handleBinaryOperation(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);

void handleNAryOperation(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);

// Subroutine to handle file-related commands
void handleIOCommand(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);

// Run commands that take no arguments
void handleNullaryCommand(const std::string &keyword, std::istream &argStream, PolygonMap &polygons);


inline
void printOk() {
    cout << "ok" << endl;
}


inline
void printError(const std::string &error) {
    // \e[31;1m is the ANSI escape sequence for bright red text
    cerr << "\e[31;1m" << "error: " << error << "\e[0m" << endl;
}

inline
void printWarning(const std::string &warning) {
    // \e[33m is the ANSI escape sequence for yellow text
    cerr << "\e[33m" << "warning: " << warning << "\e[0m" << endl;
}


// ----------------------------------------------------------------


// Maps each command keyword to its corresponding command handler
const std::map<std::string, CommandHandler> cmdHandlerMap = {
        {CMD::POLYGON,      handleIDManagement},
        {CMD::DELETE,       handleIDManagement},
        {CMD::PRINT,        handlePolygonMethod},
        {CMD::AREA,         handlePolygonMethod},
        {CMD::PERIMETER,    handlePolygonMethod},
        {CMD::VERTICES,     handlePolygonMethod},
        {CMD::CENTROID,     handlePolygonMethod},
        {CMD::SETCOL,       handlePolygonMethod},
        {CMD::INTERSECTION, handleBinaryOperation},
        {CMD::UNION,        handleBinaryOperation},
        {CMD::INSIDE,       handleBinaryOperation},
        {CMD::BBOX,         handleNAryOperation},
        {CMD::LIST,         handleNullaryCommand},
        {CMD::SAVE,         handleIOCommand},
        {CMD::LOAD,         handleIOCommand},
        {CMD::DRAW,         handleIOCommand},
        {CMD::PAINT,        handleIOCommand}
};

// Gets the command handler associated to the command `keyword`
CommandHandler getCommandHandler(const std::string &keyword);


void parseCommand(const std::string &command, PolygonMap &polygons);


#endif //CONVEXPOLYGONS_HANDLERS_H
