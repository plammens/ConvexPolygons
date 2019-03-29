// IO commands for calculator

#ifndef CONVEXPOLYGONS_COMMANDS_H
#define CONVEXPOLYGONS_COMMANDS_H

#include <iostream>
#include "polygonmap.h"
#include "range.h"


// Gets polygon with ID `id` in `polygons`; throws `UndefinedID` if nonexistent
const ConvexPolygon &getPolygon(const std::string &id, const PolygonMap &polygons);
ConvexPolygon &getPolygon(const std::string &id, PolygonMap &polygons);

ConstRange<ConvexPolygon> getPolygons(const std::vector<std::string> &polygonIDs, PolygonMap &polygons);

// Reads an ID and a sequence of points form `is`, from which a polygon is
// constructed and saved in `polygons` (with the given ID)
void readAndSavePolygon(std::istream &is, PolygonMap &polygons);

// Reads a sequence of points from `is` and saves a new polygon in `polygons`
// with ID `id`
void readAndSavePolygon(std::istream &is, PolygonMap &polygons, const std::string & id);

// Print polygon to an output stream in plain format
void printPolygon(const std::string &id, const ConvexPolygon &pol, std::ostream &os = std::cout);

// Print a list of defined polygon identifiers
void list(const PolygonMap &polygons);

// Save a list of polygons in a text file
void save(const std::string &file, const std::vector<std::string> &polygonIDs, const PolygonMap &polygons);

// Load polygons from text file
void load(const std::string &file, PolygonMap &polygons);

// Parse commands from file
void include(const std::string &file, PolygonMap &polygons, bool silent = false);


#endif //CONVEXPOLYGONS_COMMANDS_H
