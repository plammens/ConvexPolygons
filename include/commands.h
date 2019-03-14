#ifndef CONVEXPOLYGONS_COMMANDS_H
#define CONVEXPOLYGONS_COMMANDS_H

#include <set>
#include "errors.h"


typedef map<string, ConvexPolygon> PolygonMap;

const string OUT_DIR = "out/";


namespace CMD {
    const string
            POLYGON = "polygon",
            PRINT = "print",
            AREA = "area",
            PERIMETER = "perimeter",
            VERTICES = "vertices",
            CENTROID = "centroid",
            SETCOL = "setcol",
            INTERSECTION = "intersection",
            UNION = "union",
            INSIDE = "inside",
            BBOX = "bbox",
            SAVE = "save",
            LOAD = "load",
            DRAW = "draw";
}


inline void printOk() {
    cout << "ok" << endl;
}

inline void printError(const string &error) {
    cout << "error: " << error << endl;
}

// Reads a sequence of points from `is` and saves a new polygon from it in `polygons`
inline void readAndSavePolygon(istream &is, PolygonMap &polygons) {
    string id;
    is >> id;
    Points points = readVector<Point>(is);
    polygons[id] = ConvexPolygon(id, points);
}

// Save a list of polygons in a text file
void save(const string &file, const vector<string> &polygonIDs, const PolygonMap &polygons) {
    ostringstream oss;
    for (const string &id : polygonIDs) {
        const ConvexPolygon &pol = polygons.at(id);
        oss << pol << endl;
    }

    ofstream fileStream;
    fileStream.open(file);
    if (not fileStream.is_open()) throw IOError();
    fileStream << oss.str();
    fileStream.close();
}

// Load polygons from text file
void load(const string &file, PolygonMap &polygons) {
    ifstream fileStream;
    fileStream.open(file);
    if (not fileStream.is_open()) throw IOError();

    string line;
    while (getline(fileStream, line)) {
        istringstream argStream(line);
        readAndSavePolygon(argStream, polygons);
    }

    fileStream.close();
}

// Subroutine to handle commands involving a single polygon
void runPolygonMethod(const string &keyword, istream &argStream, PolygonMap &polygons) {
    if (keyword == CMD::POLYGON) {
        readAndSavePolygon(argStream, polygons);
        printOk();
    } else {
        string id;
        argStream >> id;
        // Get polygon (throws `out_of_range` if nonexistent):
        ConvexPolygon &pol = polygons.at(id);

        if (keyword == CMD::PRINT) pol.print();
        else if (keyword == CMD::AREA) cout << pol.area() << endl;
        else if (keyword == CMD::PERIMETER) cout << pol.perimeter() << endl;
        else if (keyword == CMD::VERTICES) cout << pol.vertexCount() << endl;
        else if (keyword == CMD::CENTROID);
        else if (keyword == CMD::SETCOL);
        else assert(false);  // Shouldn't get here
    }
}


// Subroutine to handle operations with polygons
void runOperationCommand(const string &command, istream &argStream, PolygonMap &polygons) {
}

// Subroutine to handle file-related commands
void runIOCommand(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string file;
    argStream >> file;
    if (file.empty()) throw SyntaxError();
    file = OUT_DIR + file;  // perfix with output directory
    vector<string> polygonIDs = readVector<string>(argStream);

    if (keyword == CMD::SAVE) save(file, polygonIDs, polygons);
    else if (keyword == CMD::LOAD) load(file, polygons);
    else if (keyword == CMD::DRAW) {}
    else assert(false); // Shouldn't get here

    printOk();
}

typedef function<void(const string &, istream &, PolygonMap &)> CommandHandler;

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

CommandHandler getCommandHandler(const string &keyword) {
    auto it = commandHandler.find(keyword);
    if (it == commandHandler.end()) throw UnrecognizedCommand();
    return it->second;
}

#endif //CONVEXPOLYGONS_COMMANDS_H
