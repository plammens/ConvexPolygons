#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cassert>
#include "../include/ConvexPolygon.h"
#include "../include/utils.h"
#include "../include/commands.h"

using namespace std;


const string OUT_DIR = "out/";


typedef map<string, ConvexPolygon> PolygonMap;


class IOError : exception {};

class SyntaxError : exception {};


// ------------------------------------------------

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

// Check whether command is valid and run corresponding subroutine
void parseCommand(const string &command, PolygonMap &polygons) {
    if (command.empty()) return;  // ignore empty lines
    try {

        istringstream iss(command);
        string keyword;
        iss >> keyword;

        if (POLYGON_CMDS.count(keyword)) runPolygonMethod(keyword, iss, polygons);
        else if (OP_CMDS.count(keyword)) runOperationCommand(keyword, iss, polygons);
        else if (IO_CMDS.count(keyword)) runIOCommand(keyword, iss, polygons);
        else if (keyword[0] == '#') cout << '#' << endl;  // handle comments
        else printError("unrecognized command");

    } catch (out_of_range &) {
        printError("undefined ID");
    } catch (IOError &) {
        printError("unable to access file");
    } catch (SyntaxError &) {
        printError("invalid command syntax");
    }
}

// ------------------------------------------------


int main() {
    PolygonMap polygons;
    string command;
    while (getline(cin, command)) parseCommand(command, polygons);
}
