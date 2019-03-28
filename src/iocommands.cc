#include "details/iocommands.h"

#include <fstream>
#include <boost/range/adaptors.hpp>
#include "errors.h"
#include "details/utils.h"

using namespace std;


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
    Points points = readVector<Point>(is);
    polygons[id] = ConvexPolygon(points);
}

void readAndSavePolygon(istream &is, PolygonMap &polygons) {
    string id;
    getArgs(is, id);
    readAndSavePolygon(is, polygons, id);
}


//////////////////////

inline
ifstream openForReading(const string &filename) {
    ifstream file;
    file.open(filename);
    if (not file.is_open()) throw IOError(filename);
    return file;
}

inline
ofstream openForWriting(const string &filename) {
    ofstream file;
    file.open(filename);
    if (not file.is_open()) throw IOError(filename);
    return file;
}


//////////////////////


void save(const string &file, const vector<string> &polygonIDs, const PolygonMap &polygons) {
    ofstream fileStream = openForWriting(file);

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
    ifstream fileStream = openForReading(file);

    string line;
    while (getline(fileStream, line)) {
        istringstream argStream(line);
        readAndSavePolygon(argStream, polygons);
    }

    fileStream.close();
}


void parseCommand(const string &, PolygonMap &);  // forward declaration

void include(const string &file, PolygonMap &polygons, bool silent) {
    ifstream fileStream = openForReading(file);
    if (silent) cout.setstate(ios_base::failbit);  // suppress output

    string line;
    while (getline(fileStream, line))
        parseCommand(line, polygons);

    cout.clear();
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


ConstRange<ConvexPolygon> getPolygons(const vector<string> &polygonIDs, PolygonMap &polygons) {
    // This unary lambda "gets" a polygon from the map given its ID
    function<const ConvexPolygon &(const string &id)> getter =
            [&polygons](const string &id) -> ConvexPolygon & {
                return getPolygon(id, polygons);
            };
    // (Lazily) apply the lambda to each ID:
    return boost::adaptors::transform(polygonIDs, getter);
}
