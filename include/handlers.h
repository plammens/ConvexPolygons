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
void runPolygonManagement(const string &keyword, istream &argStream, PolygonMap &polygons);

// Subroutine to handle commands involving printing info about a single polygon
void runPolygonMethod(const string &keyword, istream &argStream, PolygonMap &polygons);

// Subroutine to handle operations with polygons
void runOperationCommand(const string &keyword, istream &argStream, PolygonMap &polygons);

// Subroutine to handle file-related commands
void runIOCommand(const string &keyword, istream &argStream, PolygonMap &polygons);

// Run commands that take no arguments
void runNullaryCommand(const string &keyword, istream &argStream, PolygonMap &polygons);


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
        {CMD::POLYGON,      runPolygonManagement},
        {CMD::PRINT,        runPolygonMethod},
        {CMD::AREA,         runPolygonMethod},
        {CMD::PERIMETER,    runPolygonMethod},
        {CMD::VERTICES,     runPolygonMethod},
        {CMD::CENTROID,     runPolygonMethod},
        {CMD::SETCOL,       runPolygonMethod},
        {CMD::INTERSECTION, runOperationCommand},
        {CMD::UNION,        runOperationCommand},
        {CMD::INSIDE,       runOperationCommand},
        {CMD::BBOX,         runOperationCommand},
        {CMD::LIST,         runNullaryCommand},
        {CMD::SAVE,         runIOCommand},
        {CMD::LOAD,         runIOCommand},
        {CMD::DRAW,         runIOCommand}
};

// Gets the command handler associated to the command `keyword`
CommandHandler getCommandHandler(const string &keyword);


#endif //CONVEXPOLYGONS_HANDLERS_H
