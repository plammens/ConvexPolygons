#include <iostream>
#include <handlers.h>


#include "handlers.h"
#include "errors.h"
#include "utils.h"


void handleIDManagement(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string id;
    getArgs(argStream, id);

    if      (keyword == CMD::POLYGON) readAndSavePolygon(argStream, polygons, id);
    else if (keyword == CMD::DELETE) polygons.erase(id);
    else assert(false);

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


void handleBinaryOperation(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string id1, id2, id3;
    getArgs(argStream, id1, id2);
    argStream >> id3;  // no exception if not available

    if      (keyword == CMD::INTERSECTION);
    else if (keyword == CMD::UNION) {
        if (id3.empty()) polygons[id1].convexUnion(getPolygon(id2, polygons));
        else polygons[id1] = convexUnion(getPolygon(id2, polygons), getPolygon(id3, polygons));
    }
    else if (keyword == CMD::INSIDE);
    else assert(false);

    printOk();
}


void handleNAryOperation(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string id;
    getArgs(argStream, id);
    vector<string> polIDs = readVector<string>(argStream);

    if (keyword == CMD::BBOX) polygons[id] = boundingBox(polIDs, polygons);
    else assert(false);

    printOk();
}


void handleIOCommand(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string file;
    argStream >> file;
    if (file.empty()) throw SyntaxError("no file specified");
    prefixPath(file, IO::OUT_DIR);  // prefix with output directory
    vector<string> polygonIDs = readVector<string>(argStream);

    if      (keyword == CMD::SAVE) save(file, polygonIDs, polygons);
    else if (keyword == CMD::LOAD) load(file, polygons);
    else if (keyword == CMD::DRAW) draw(file, polygonIDs, polygons);
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
