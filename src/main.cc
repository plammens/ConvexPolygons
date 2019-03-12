#include <iostream>
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


// ------------------------------------------------

inline
void printOk() {
    cout << "ok" << endl;
}

inline
void printError(const string &error) {
    cout << "error: " << error << endl;
}


// Subroutine to handle commands involving a single polygon
void runPolygonMethod(const string &command, PolygonMap &polygons) {
    string id;
    cin >> id;

    if (command == "polygon") {
        Points points = readLineAsVector<Point>();
        polygons[id] = ConvexPolygon(id, points);
        printOk();
    }
    else {
        try {
            // Get polygon (throws `out_of_range` if nonexistent):
            ConvexPolygon &P = polygons.at(id);

            if (command == "print") P.print();
            else if (command == "area") cout << P.area() << endl;
            else if (command == "perimeter");
            else if (command == "vertices") cout << P.vertexCount() << endl;
            else if (command == "centroid");
            else if (command == "setcol");
            else
                assert(false);  // Shouldn't get here

        }
        catch (out_of_range &) { printError("undefined identifier"); }
    }
}

// Subroutine to handle operations with polygons
void runOperationCommand(const string &command, PolygonMap &polygons) {
}

// Subroutine to handle file-related commands
void runIOCommand(const string &command, PolygonMap &polygons) {
    string file;
    cin >> file;

    if (command == "save") {}
    else if (command == "load") {}
    else if (command == "draw") {}

    printOk();
}

// Check whether command exists and run corresponding subroutine
void parseCommand(const string &command, PolygonMap &polygons) {
    if (POLYGON_CMDS.count(command)) runPolygonMethod(command, polygons);
    else if (OP_CMDS.count(command)) runOperationCommand(command, polygons);
    else if (IO_CMDS.count(command)) runIOCommand(command, polygons);
    else printError("unrecognized command");
}

// ------------------------------------------------


int main() {
    cout.setf(ios::fixed);
    cout.precision(3);

    PolygonMap polygons;
    string command;
    while (cin >> command) parseCommand(command, polygons);
}
