#include <fstream>
#include "../include/commands.h"
#include "../include/errors.h"
#include "../include/utils.h"


void readAndSavePolygon(istream &is, PolygonMap &polygons) {
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

