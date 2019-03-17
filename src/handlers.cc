#include <iostream>
#include <handlers.h>

#include "errors.h"
#include "utils.h"


void handlePolygonManagement(const string &keyword, istream &argStream, PolygonMap &polygons) {
    assert(keyword == CMD::POLYGON);  // TODO: remove assert
    readAndSavePolygon(argStream, polygons);
    printOk();
}


void handlePolygonMethod(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string id;
    getArgs(argStream, id);
    ConvexPolygon &pol = getPolygon(id, polygons);  // throws `UndefinedID` if nonexistent

    if      (keyword == CMD::PRINT) printPolygon(id, pol);
    else if (keyword == CMD::AREA) cout << pol.area() << endl;
    else if (keyword == CMD::PERIMETER) cout << pol.perimeter() << endl;
    else if (keyword == CMD::VERTICES) cout << pol.vertexCount() << endl;
    else if (keyword == CMD::CENTROID) cout << pol.centroid() << endl;
    else if (keyword == CMD::SETCOL) {
        double r, g, b;
        getArgs(argStream, r, g, b);
             pol.setColor(r, g, b);
        printOk();
    }
    else assert(false);  // Shouldn't get here
}


void handlePolygonOperation(const string &keyword, istream &argStream, PolygonMap &polygons) {
    // TODO: operation commands
}


void handleIOCommand(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string file;
    argStream >> file;
    if (file.empty()) throw SyntaxError("no file specified");
    file = OUT_DIR + file;  // prefix with output directory
    vector<string> polygonIDs = readVector<string>(argStream);

    if      (keyword == CMD::SAVE) save(file, polygonIDs, polygons);
    else if (keyword == CMD::LOAD) load(file, polygons);
    else if (keyword == CMD::DRAW);
    else assert(false); // Shouldn't get here

    printOk();
}


void handleNullaryCommand(const string &keyword, istream &argStream, PolygonMap &polygons) {
    if (keyword == CMD::LIST) list(polygons);
    else assert(false); // Shouldn't get here

    if (not (argStream >> ws).eof()) throw UnusedArgument(format("`%` takes no arguments", keyword));
}


// -------------------

CommandHandler getCommandHandler(const string &keyword) {
    auto it = cmdHandlerMap.find(keyword);
    if (it == cmdHandlerMap.end()) throw UnknownCommand(keyword);
    return it->second;
}
