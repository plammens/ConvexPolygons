#ifndef CONVEXPOLYGONS_HANDLERS_H
#define CONVEXPOLYGONS_HANDLERS_H

#include <functional>
#include <cassert>
#include "commands.h"


// Command handler signature
typedef function<void(const string &, istream &, PolygonMap &)> CommandHandler;


// ---------------------------------------------------------------


// non-const version

// Subroutine to handle creation/assignment of a single polygon
void handleIDManagement(const string &keyword, istream &argStream, PolygonMap &polygons);

// Subroutine to handle commands involving printing info about a single polygon
void handlePolygonMethod(const string &keyword, istream &argStream, PolygonMap &polygons);

// Subroutine to handle operations with polygons
void handleBinaryOperation(const string &keyword, istream &argStream, PolygonMap &polygons);

void handleNAryOperation(const string &keyword, istream &argStream, PolygonMap &polygons);

// Subroutine to handle file-related commands
void handleIOCommand(const string &keyword, istream &argStream, PolygonMap &polygons);

// Run commands that take no arguments
void handleNullaryCommand(const string &keyword, istream &argStream, PolygonMap &polygons);


inline
void printOk() {
    cout << "ok" << endl;
}


inline
void printError(const string &error) {
    // \e[31;1m is the ANSI escape sequence for bright red text
    cout << "\e[31;1m" << "error: " << error << "\e[0m" << endl;
}

inline
void printWarning(const string &warning) {
    // \e[33m is the ANSI escape sequence for yellow text
    cout << "\e[33m" << "warning: " << warning << "\e[0m" << endl;
}


// ----------------------------------------------------------------


// Maps each command keyword to its corresponding command handler
const map<string, CommandHandler> cmdHandlerMap = {
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
        {CMD::DRAW,         handleIOCommand}
};

// Gets the command handler associated to the command `keyword`
CommandHandler getCommandHandler(const string &keyword);


#endif //CONVEXPOLYGONS_HANDLERS_H
