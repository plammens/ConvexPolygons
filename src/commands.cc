#include <iostream>
#include <fstream>
#include <commands.h>

#include "handlers.h"
#include "errors.h"
#include "utils.h"


const ConvexPolygon &getPolygon(const string &id, const PolygonMap &polygons) {
    auto it = polygons.find(id);
    if (it == polygons.end()) throw UndefinedID(id);
    return it->second;
}


ConvexPolygon &getPolygon(const string &id, PolygonMap &polygons) {
    // Behaviour is same as const version, so we just cast away to avoid duplication
    return const_cast<ConvexPolygon &>(getPolygon(id, const_cast<const PolygonMap &>(polygons)));
}


void readAndSavePolygon(istream &is, PolygonMap &polygons, const string &id) {
    if (id.empty()) getArgs(is, const_cast<string &>(id));  // if no `id` argument given, read it
    Points points = readVector<Point>(is);
    polygons[id] = ConvexPolygon(points);
}


void save(const string &file, const vector<string> &polygonIDs, const PolygonMap &polygons) {
    ofstream fileStream;
    fileStream.open(file);
    if (not fileStream.is_open()) throw IOError(file);

    // We buffer the result so we can catch errors before we write to the file
    ostringstream oss;
    for (const string &id : polygonIDs) {
        const ConvexPolygon &pol = getPolygon(id, polygons);  // may throw UndefinedID
        printPolygon(id, pol, fileStream);
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


void printPolygon(const string &id, const ConvexPolygon &pol, ostream &os) {
    os << id;
    for (const Point &P : pol.getVertices())
        os << ' ' << P;
    os << endl;
}


void list(const PolygonMap &polygons) {
    if (not polygons.empty()) {
        auto it = polygons.begin();
        cout << it->first;
        for (++it; it != polygons.end(); ++it)
            cout << ' ' << it->first;
    }
    cout << endl;
}
