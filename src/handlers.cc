#include <iostream>
#include "../include/handlers.h"
#include "../include/errors.h"
#include "../include/utils.h"


const ConvexPolygon &getPolygon(const string &id, const PolygonMap &polygons) {
    auto it = polygons.find(id);
    if (it == polygons.end()) throw UndefinedID(id);
    return it->second;
}

ConvexPolygon &getPolygon(const string &id, PolygonMap &polygons) {
    // Behaviour is same as const version, so we just cast away to avoid duplication
    return const_cast<ConvexPolygon &>(getPolygon(id, const_cast<const PolygonMap &>(polygons)));
}

void runPolygonMethod(const string &keyword, istream &argStream, PolygonMap &polygons) {
    if (keyword == CMD::POLYGON) {
        readAndSavePolygon(argStream, polygons);
        printOk();
    } else {
        string id;
        argStream >> id;
        ConvexPolygon &pol = getPolygon(id, polygons);  // throws `UndefinedID` if nonexistent

        if (keyword == CMD::PRINT) pol.print();
        else if (keyword == CMD::AREA) cout << pol.area() << endl;
        else if (keyword == CMD::PERIMETER) cout << pol.perimeter() << endl;
        else if (keyword == CMD::VERTICES) cout << pol.vertexCount() << endl;
        else if (keyword == CMD::CENTROID);  // TODO: centroid
        else if (keyword == CMD::SETCOL);  // TODO: setcol
        else assert(false);  // Shouldn't get here
    }
}

void runOperationCommand(const string &keyword, istream &argStream, PolygonMap &polygons) {
    // TODO: operation commands
}

void runIOCommand(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string file;
    argStream >> file;
    if (file.empty()) throw SyntaxError("no file specified");
    file = OUT_DIR + file;  // prefix with output directory
    vector<string> polygonIDs = readVector<string>(argStream);

    if (keyword == CMD::SAVE) save(file, polygonIDs, polygons);
    else if (keyword == CMD::LOAD) load(file, polygons);
    else if (keyword == CMD::DRAW) {}
    else assert(false); // Shouldn't get here

    printOk();
}

CommandHandler getCommandHandler(const string &keyword) {
    auto it = commandHandler.find(keyword);
    if (it == commandHandler.end()) throw UnrecognizedCommand(keyword);
    return it->second;
}
