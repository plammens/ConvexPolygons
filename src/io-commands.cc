#include "io-commands.h"

#include <fstream>
#include <boost/range/adaptors.hpp>  // boost::adaptors::transform
#include "details/utils.h"  // readVector
#include "errors.h"



//-------- INTERNAL HELPER FUNCTIONS --------//

inline
void _open(std::ifstream &stream, const std::string &filename) {
    stream.open(filename);
    if (not stream.is_open()) throw error::IOError(filename);
}

inline
void _open(std::ofstream &stream, const std::string &filename) {
    stream.open(filename);
    if (not stream.is_open()) throw error::IOError(filename);
}




//-------- EXPOSED FUNCTIONS --------//

void readPolygon(std::istream &is, PolygonMap &polygonMap) {
    std::string id;
    getArgs(is, id);
    readPolygon(is, polygonMap, id);
}


void readPolygon(std::istream &is, PolygonMap &polygons, const std::string &id) {
    Points points = readVector<Point>(is);
    polygons[id] = ConvexPolygon(points);
}


void printPolygon(const std::string &id, const ConvexPolygon &pol, std::ostream &os) {
    os << id;

    const Points &vertices = pol.getVertices();
    const long end = vertices.size() - 1;
    // we use ints instead of iterators to keep the less-than comparison safe for empty polygons
    for (long i = 0; i < end; ++i)
        os << ' ' << vertices[i];

    os << std::endl;
}


void prettyPrint(const std::string &id, const ConvexPolygon &pol, std::ostream &os) {
    os << id;

    const Points &vertices = pol.getVertices();
    const long end = vertices.size() - 1;
    // we use ints instead of iterators to keep the less-than comparison safe for empty polygons
    for (long i = 0; i < end; ++i)
        os << " (" << vertices[i].x << ", " << vertices[i].y << ")";

    os << std::endl;
}


void save(const std::string &file, const std::vector<std::string> &polygonIDs, const PolygonMap &polygonMap) {
    std::ofstream fileStream;
    _open(fileStream, file);

    // We buffer the result so we can catch errors before we write to the file
    std::ostringstream oss;
    for (const std::string &id : polygonIDs) {
        const ConvexPolygon &pol = getPolygon(id, polygonMap);  // may throw UndefinedID
        printPolygon(id, pol, fileStream);
    }

    fileStream << oss.str();
    fileStream.close();
}


void load(const std::string &file, PolygonMap &polygons) {
    std::ifstream fileStream;
    _open(fileStream, file);

    std::string line;
    while (getline(fileStream, line)) {
        std::istringstream argStream(line);
        readPolygon(argStream, polygons);
    }

    fileStream.close();
}


void parseCommand(const std::string &, PolygonMap &);  // forward declaration; defined in `details/handlers.cc`

void include(const std::string &file, PolygonMap &polygonMap, bool silent) {
    std::ifstream fileStream;
    _open(fileStream, file);
    if (silent) std::cout.setstate(std::ios_base::failbit);  // suppress output

    std::string line;
    while (getline(fileStream, line))
        parseCommand(line, polygonMap);

    std::cout.clear();
    fileStream.close();
}



void list(const PolygonMap &polygonMap) {
    if (not polygonMap.empty()) {
        auto it = polygonMap.begin();
        std::cout << it->first;
        for (++it; it != polygonMap.end(); ++it)
            std::cout << ' ' << it->first;
    }
    std::cout << std::endl;
}



//-------- GET POLYGON --------//

const ConvexPolygon &getPolygon(const std::string &id, const PolygonMap &polygonMap) {
    auto it = polygonMap.find(id);
    if (it == polygonMap.end()) throw error::UndefinedID(id);
    return it->second;
}


ConvexPolygon &getPolygon(const std::string &id, PolygonMap &polygons) {
    // Behaviour is same as const version, so we just cast away to avoid duplication
    return const_cast<ConvexPolygon &>(getPolygon(id, const_cast<const PolygonMap &>(polygons)));
}

ConstRange<ConvexPolygon> getPolygons(const std::vector<std::string> &polygonIDs, const PolygonMap &polygonMap) {
    // This unary lambda "gets" a polygon from the map given its ID
    auto getter = [&polygonMap](const std::string &id) -> const ConvexPolygon & {
        return getPolygon(id, polygonMap);
    };

    // (Lazily) apply the lambda to each ID:
    return boost::adaptors::transform(polygonIDs, getter);
}

