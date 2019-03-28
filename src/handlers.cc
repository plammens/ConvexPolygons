#include "class/ConvexPolygon.h"
#include <iostream>
#include "details/handlers.h"

#include <cassert>
#include "details/iocommands.h"  // save, load, list...
#include "details/draw.h"  // draw
#include "errors.h"
#include "details/utils.h"  // getArgs


void handleIDManagement(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string id;
    getArgs(argStream, id);

    if (keyword == CMD::POLYGON) readAndSavePolygon(argStream, polygons, id);
    else if (keyword == CMD::DELETE) polygons.erase(id);
    else assert(false);

    printOk();
}


void handlePolygonMethod(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string id;
    getArgs(argStream, id);
    ConvexPolygon &pol = getPolygon(id, polygons);  // throws `UndefinedID` if nonexistent

    if (keyword == CMD::PRINT) printPolygon(id, pol);
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


void handleBinaryOperation(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string id1, id2, id3;
    getArgs(argStream, id1, id2);
    argStream >> id3;  // no exception if not available

    // arguments to the operation:
    const ConvexPolygon &p1 = getPolygon(id3.empty() ? id1 : id2, polygons);
    const ConvexPolygon &p2 = getPolygon(id3.empty() ? id2 : id3, polygons);

    if      (keyword == CMD::INSIDE) {
        cout << (isInside(p1, p2) ? "yes" : "no") << endl;
        return;
    }
    else if (keyword == CMD::UNION) polygons[id1] = convexUnion(p1, p2);
    else if (keyword == CMD::INTERSECTION) polygons[id1] = intersection(p1, p2);
    else assert(false);

    printOk();
}


void handleNAryOperation(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string id;
    getArgs(argStream, id);
    vector<string> polIDs = readVector<string>(argStream);

    if (keyword == CMD::BBOX)
        polygons[id] = boundingBox(getPolygons(polIDs, polygons));
    else assert(false);

    printOk();
}


void handleIOCommand(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string file;
    argStream >> file;
    if (file.empty()) throw SyntaxError("no file specified");
    prefixPath(file, IO::OUT_DIR);  // prefix with output directory
    vector<string> polygonIDs = readVector<string>(argStream);

    if (keyword == CMD::SAVE) save(file, polygonIDs, polygons);
    else if (keyword == CMD::LOAD) load(file, polygons);
    else if (keyword == CMD::DRAW) draw(file, getPolygons(polygonIDs, polygons));
    else if (keyword == CMD::PAINT) draw(file, getPolygons(polygonIDs, polygons), true);
    else if (keyword == CMD::INCLUDE) include(file, polygons);
    else assert(false); // Shouldn't get here

    printOk();
}


void handleNullaryCommand(const string &keyword, istream &argStream, PolygonMap &polygons) {
    if (keyword == CMD::LIST) list(polygons);
    else assert(false); // Shouldn't get here
}

// -------------------


CommandHandler getCommandHandler(const string &keyword) {
    auto it = cmdHandlerMap.find(keyword);
    if (it == cmdHandlerMap.end()) throw UnknownCommand(keyword);
    return it->second;
}


// Check whether command is valid and run corresponding handler
void parseCommand(const string &command, PolygonMap &polygons) {
    if (command.empty()) return;  // ignore empty lines

    try {
        istringstream iss(command);
        string keyword;
        iss >> keyword;
        if (keyword[0] == '#') { cout << '#' << endl; return; }  // comments

        // Get appropriate handler: (may throw `UnknownCommand`)
        CommandHandler handler = getCommandHandler(keyword);
        handler(keyword, iss, polygons);
        if (not (iss >> ws).eof()) throw UnusedArgument();  // check unused arguments

    } catch (Error &error) {
        printError(error.what());
    } catch (Warning &warning) {
        printWarning(warning.what());
    }
}