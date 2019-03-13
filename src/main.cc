#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <cassert>
#include "../include/ConvexPolygon.h"
#include "../include/utils.h"

using namespace std;


const set<string> POLYGON_CMDS = {
        "polygon",
        "print",
        "area",
        "perimeter",
        "vertices",
        "centroid",
        "setcol"
};

const set<string> OP_CMDS = {
        "intersection",
        "union",
        "inside",
        "bbox"
};

const set<string> IO_CMDS = {
        "save",
        "load",
        "draw"
};


typedef map<string, ConvexPolygon> PolygonMap;


class IOError : exception {};
class SyntaxError : exception {};


// ------------------------------------------------

inline
void printOk() {
    cout << "ok" << endl;
}

inline
void printError(const string &error) {
    cout << "error: " << error << endl;
}

// Discards line of input
inline
void handleComment() {
    string comment;
    getline(cin, comment);
    cout << '#' << endl;
}


// Subroutine to handle commands involving a single polygon
void runPolygonMethod(const string &keyword, istream &argStream, PolygonMap &polygons) {
    string id;
    argStream >> id;

    if (keyword == "polygon") {
        Points points = readVector<Point>();
        polygons[id] = ConvexPolygon(id, points);
        printOk();
    }
    else {
        // Get polygon (throws `out_of_range` if nonexistent):
        ConvexPolygon &pol = polygons.at(id);

        if (keyword == "print") pol.print();
        else if (keyword == "area") cout << pol.area() << endl;
        else if (keyword == "perimeter") cout << pol.perimeter() << endl;
        else if (keyword == "vertices") cout << pol.vertexCount() << endl;
        else if (keyword == "centroid");
        else if (keyword == "setcol");
        else assert(false);  // Shouldn't get here
    }
}

// Subroutine to handle operations with polygons
void runOperationCommand(const string &command, istream &argStream, PolygonMap &polygons) {
}

// Subroutine to handle file-related commands
void runIOCommand(const string &command, istream &argStream, PolygonMap &polygons) {
    string file;
    argStream >> file;
    if (file.empty()) throw SyntaxError();
    vector<string> polygonIDs = readVector<string>(argStream);

    if (command == "save") save(file, polygonIDs, polygons);
    else if (command == "load") {}
    else if (command == "draw") {}

    printOk();
}

// Check whether command is valid and run corresponding subroutine
void parseCommand(const string &command, PolygonMap &polygons) {
    try {

        istringstream iss(command);
        string keyword;
        iss >> keyword;

        if (POLYGON_CMDS.count(keyword)) runPolygonMethod(keyword, iss, polygons);
        else if (OP_CMDS.count(keyword)) runOperationCommand(keyword, iss, polygons);
        else if (IO_CMDS.count(keyword)) runIOCommand(keyword, iss, polygons);
        else if (keyword[0] == '#') handleComment();
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
    cout.setf(ios::fixed);
    cout.precision(3);

    PolygonMap polygons;
    string command;
    while (getline(cin, command)) parseCommand(command, polygons);
}
