#ifndef CONVEXPOLYGONS_HANDLERS_H
#define CONVEXPOLYGONS_HANDLERS_H

#include <functional>
#include <cassert>
#include "commands.h"


// Command handler signature
typedef function<void(const string &, istream &, PolygonMap &)> CommandHandler;


// ---------------------------------------------------------------


// Gets polygon with ID `id` in `polygons`; throws `UndefinedID` if nonexistent
const ConvexPolygon &getPolygon(const string &id, const PolygonMap &polygons);
ConvexPolygon &getPolygon(const string &id, PolygonMap &polygons);  // non-const version

// Subroutine to handle commands involving a single polygon
void runPolygonMethod(const string &keyword, istream &argStream, PolygonMap &polygons);

// Subroutine to handle operations with polygons
void runOperationCommand(const string &keyword, istream &argStream, PolygonMap &polygons);

// Subroutine to handle file-related commands
void runIOCommand(const string &keyword, istream &argStream, PolygonMap &polygons);

inline
void printOk() {
    cout << "ok" << endl;
}

inline
void printError(const string &error) {
    cout << "error: " << error << endl;
}


// ----------------------------------------------------------------


// Maps each command keyword to its corresponding command handler
const map<string, CommandHandler> commandHandler = {
        {CMD::POLYGON,      runPolygonMethod},
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
        {CMD::SAVE,         runIOCommand},
        {CMD::LOAD,         runIOCommand},
        {CMD::DRAW,         runIOCommand}
};

// Gets the command handler associated to the command `keyword`
CommandHandler getCommandHandler(const string &keyword);


#endif //CONVEXPOLYGONS_HANDLERS_H
