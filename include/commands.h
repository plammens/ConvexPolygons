#ifndef CONVEXPOLYGONS_COMMANDS_H
#define CONVEXPOLYGONS_COMMANDS_H

#include <map>
#include "consts.h"
#include "class/ConvexPolygon.h"

using namespace std;

typedef map<string, ConvexPolygon> PolygonMap;


// Gets polygon with ID `id` in `polygons`; throws `UndefinedID` if nonexistent
const ConvexPolygon &getPolygon(const string &id, const PolygonMap &polygons);
ConvexPolygon &getPolygon(const string &id, PolygonMap &polygons);

Range<ConvexPolygon> getPolygons(const vector<string> &polygonIDs, PolygonMap &polygons);

// Reads a sequence of points from `is` and saves a new polygon from it in `polygons`
void readAndSavePolygon(istream &is, PolygonMap &polygons, const string &id = "");

// Print polygon to an output stream in plain format
void printPolygon(const string &id, const ConvexPolygon &pol, ostream &os = cout);

// Print a list of defined polygon identifiers
void list(const PolygonMap &polygons);

// Save a list of polygons in a text file
void save(const string &file, const vector<string> &polygonIDs, const PolygonMap &polygons);

// Load polygons from text file
void load(const string &file, PolygonMap &polygons);

ConvexPolygon boundingBox(Range<ConvexPolygon> polygons);

#endif //CONVEXPOLYGONS_COMMANDS_H

#include "draw.h"  // Extend with draw header
