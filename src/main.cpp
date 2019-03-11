#include <iostream>
#include <map>
#include "../include/ConvexPolygon.h"
#include "../include/utils.h"

using namespace std;

typedef map<string, ConvexPolygon> PolygonMap;


inline
void handleMissingID() {
    cout << "error: undefined identifier" << endl;
}


void parseCommand(const string &command, PolygonMap &polygons) {
    if (command == "polygon") {
        string id;
        cin >> id;
        Points points = readLineAsVec<Point>();
        polygons[id] = ConvexPolygon(id, points);
        cout << "ok" << endl;
    } else if (command == "print") {
        string id;
        cin >> id;
        try { polygons.at(id).print(); }
        catch (out_of_range) { handleMissingID(); }
    }
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(3);

    PolygonMap polygons;
    string command;
    while (cin >> command) parseCommand(command, polygons);
}
