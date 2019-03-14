
#include <handlers.h>

#include "../include/handlers.h"
#include "../include/errors.h"
#include "../include/utils.h"



ConvexPolygon &getPolygon(const string &id, PolygonMap &polygons) {
    auto it = polygons.find(id);
    if (it == polygons.end()) throw UndefinedID();
    return it->second;
}

void runPolygonMethod(const string &keyword, istream &argStream, PolygonMap &polygons) {
    if (keyword == CMD::POLYGON) {
        readAndSavePolygon(argStream, polygons);
        printOk();
    } else {
        string id;
        argStream >> id;
        // Get polygon (throws `UndefinedID` if nonexistent):
        ConvexPolygon &pol = getPolygon(id, polygons);

        if (keyword == CMD::PRINT) pol.print();
        else if (keyword == CMD::AREA) cout << pol.area() << endl;
        else if (keyword == CMD::PERIMETER) cout << pol.perimeter() << endl;
        else if (keyword == CMD::VERTICES) cout << pol.vertexCount() << endl;
        else if (keyword == CMD::CENTROID);
        else if (keyword == CMD::SETCOL);
        else assert(false);  // Shouldn't get here
    }
}

void runOperationCommand(const string &keyword, istream &argStream, PolygonMap &polygons) {
}

void runIOCommand(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string file;
    argStream >> file;
    if (file.empty()) throw SyntaxError();
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
    if (it == commandHandler.end()) throw UnrecognizedCommand();
    return it->second;
}
