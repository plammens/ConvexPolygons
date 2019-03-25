// IO commands for calculator

#ifndef CONVEXPOLYGONS_COMMANDS_H
#define CONVEXPOLYGONS_COMMANDS_H

#include <map>
#include "class/ConvexPolygon.h"
#include "aliases.h"


using namespace std;

typedef map<string, ConvexPolygon> PolygonMap;


// Gets polygon with ID `id` in `polygons`; throws `UndefinedID` if nonexistent
const ConvexPolygon &getPolygon(const string &id, const PolygonMap &polygons);
ConvexPolygon &getPolygon(const string &id, PolygonMap &polygons);

Range<ConvexPolygon> getPolygons(const vector<string> &polygonIDs, PolygonMap &polygons);

// Reads an ID and a sequence of points form `is`, from which a polygon is
// constructed and saved in `polygons` (with the given ID)
void readAndSavePolygon(istream &is, PolygonMap &polygons);

// Reads a sequence of points from `is` and saves a new polygon in `polygons`
// with ID `id`
void readAndSavePolygon(istream &is, PolygonMap &polygons, const string & id);

// Print polygon to an output stream in plain format
void printPolygon(const string &id, const ConvexPolygon &pol, ostream &os = cout);

// Print a list of defined polygon identifiers
void list(const PolygonMap &polygons);

// Save a list of polygons in a text file
void save(const string &file, const vector<string> &polygonIDs, const PolygonMap &polygons);

// Load polygons from text file
void load(const string &file, PolygonMap &polygons);


#endif //CONVEXPOLYGONS_COMMANDS_H

#include "draw.h"  // Extend with draw header
