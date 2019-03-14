#include <fstream>
#include "../include/handlers.h"
#include "../include/errors.h"
#include "../include/utils.h"


void readAndSavePolygon(istream &is, PolygonMap &polygons) {
    string id;
    is >> id;
    Points points = readVector<Point>(is);
    polygons[id] = ConvexPolygon(id, points);
}

void save(const string &file, const vector<string> &polygonIDs, const PolygonMap &polygons) {
    ofstream fileStream;
    fileStream.open(file);
    if (not fileStream.is_open()) throw IOError(file);

    // We buffer the result so we can catch errors before we write to the file
    ostringstream oss;
    for (const string &id : polygonIDs) {
        const ConvexPolygon &pol = getPolygon(id, polygons);  // may throw UndefinedID
        oss << pol << endl;
    }

    fileStream << oss.str();
    fileStream.close();
}

void load(const string &file, PolygonMap &polygons) {
    ifstream fileStream;
    fileStream.open(file);
    if (not fileStream.is_open()) throw IOError(file);

    string line;
    while (getline(fileStream, line)) {
        istringstream argStream(line);
        readAndSavePolygon(argStream, polygons);
    }

    fileStream.close();
}

