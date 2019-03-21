#include <iostream>
#include <fstream>
#include <commands.h>
#include <boost/range/adaptors.hpp>

#include "commands.h"
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

    const Points &vertices = pol.getVertices();
    const long end = vertices.size() - 1;
    for (long i = 0; i < end; ++i)
        os << ' ' << vertices[i];

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


ConvexPolygon boundingBox(Range<ConvexPolygon> polygons) {
    // skip empty polygons:
    polygons = boost::adaptors::filter(polygons, [](const ConvexPolygon &pol){ return not pol.empty(); });
    // if, after filtering, polygons is empty, throw an error
    if (polygons.empty()) throw ValueError("bounding box undefined for empty set");

    Point SW = {INFINITY, INFINITY};
    Point NE = {-INFINITY, -INFINITY};
    for (const ConvexPolygon &pol : polygons) {
        ConvexPolygon bbox = pol.boundingBox();
        SW = bottomLeft(SW, pol.boundingBox().getVertices()[0]);  // TODO: subclass?
        NE = upperRight(NE, pol.boundingBox().getVertices()[2]);
    }

    Point NW = {SW.x, NE.y};
    Point SE = {NE.x, SW.y};

    Points boxVertices = {SW, NW, NE, SE};
    return ConvexPolygon(boxVertices);
}


Range<ConvexPolygon> getPolygons(const vector<string> &polygonIDs, PolygonMap &polygons) {
    // This unary lambda "gets" a polygon from the map given its ID
    function<const ConvexPolygon &(const string &id)> getter =
            [&polygons](const string &id) -> ConvexPolygon & {
                return getPolygon(id, polygons);
            };
    // (Lazily) apply the lambda to each ID:
    return boost::adaptors::transform(polygonIDs, getter);
}
