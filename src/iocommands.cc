#include "details/iocommands.h"

#include <fstream>
#include <boost/range/adaptors.hpp>
#include "errors.h"
#include "details/utils.h"


const ConvexPolygon &getPolygon(const std::string &id, const PolygonMap &polygons) {
    auto it = polygons.find(id);
    if (it == polygons.end()) throw UndefinedID(id);
    return it->second;
}


ConvexPolygon &getPolygon(const std::string &id, PolygonMap &polygons) {
    // Behaviour is same as const version, so we just cast away to avoid duplication
    return const_cast<ConvexPolygon &>(getPolygon(id, const_cast<const PolygonMap &>(polygons)));
}


void readAndSavePolygon(std::istream &is, PolygonMap &polygons, const std::string &id) {
    Points points = readVector<Point>(is);
    polygons[id] = ConvexPolygon(points);
}

void readAndSavePolygon(std::istream &is, PolygonMap &polygons) {
    std::string id;
    getArgs(is, id);
    readAndSavePolygon(is, polygons, id);
}


//////////////////////

inline
void open(std::ifstream &stream, const std::string &filename) {
    stream.open(filename);
    if (not stream.is_open()) throw IOError(filename);
}

inline
void open(std::ofstream &stream, const std::string &filename) {
    stream.open(filename);
    if (not stream.is_open()) throw IOError(filename);
}


//////////////////////


void save(const std::string &file, const std::vector<std::string> &polygonIDs, const PolygonMap &polygons) {
    std::ofstream fileStream; open(fileStream, file);

    // We buffer the result so we can catch errors before we write to the file
    std::ostringstream oss;
    for (const std::string &id : polygonIDs) {
        const ConvexPolygon &pol = getPolygon(id, polygons);  // may throw UndefinedID
        printPolygon(id, pol, fileStream);
    }

    fileStream << oss.str();
    fileStream.close();
}

void load(const std::string &file, PolygonMap &polygons) {
    std::ifstream fileStream; open(fileStream, file);

    std::string line;
    while (getline(fileStream, line)) {
        std::istringstream argStream(line);
        readAndSavePolygon(argStream, polygons);
    }

    fileStream.close();
}


void parseCommand(const std::string &, PolygonMap &);  // forward declaration

void include(const std::string &file, PolygonMap &polygons, bool silent) {
    std::ifstream fileStream; open(fileStream, file);
    if (silent) std::cout.setstate(std::ios_base::failbit);  // suppress output

    std::string line;
    while (getline(fileStream, line))
        parseCommand(line, polygons);

    std::cout.clear();
    fileStream.close();
}


void printPolygon(const std::string &id, const ConvexPolygon &pol, std::ostream &os) {
    os << id;

    const Points &vertices = pol.getVertices();
    const long end = vertices.size() - 1;
    for (long i = 0; i < end; ++i)
        os << ' ' << vertices[i];

    os << std::endl;
}


void list(const PolygonMap &polygons) {
    if (not polygons.empty()) {
        auto it = polygons.begin();
        std::cout << it->first;
        for (++it; it != polygons.end(); ++it)
            std::cout << ' ' << it->first;
    }
    std::cout << std::endl;
}


ConstRange<ConvexPolygon> getPolygons(const std::vector<std::string> &polygonIDs, PolygonMap &polygons) {
    // This unary lambda "gets" a polygon from the map given its ID
    std::function<const ConvexPolygon &(const std::string &id)> getter =
            [&polygons](const std::string &id) -> ConvexPolygon & {
                return getPolygon(id, polygons);
            };
    // (Lazily) apply the lambda to each ID:
    return boost::adaptors::transform(polygonIDs, getter);
}
