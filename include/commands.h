#ifndef CONVEXPOLYGONS_COMMANDS_H
#define CONVEXPOLYGONS_COMMANDS_H

#include <string>
#include <map>
#include "class/ConvexPolygon.h"


typedef map<string, ConvexPolygon> PolygonMap;


// Names of all avaliable command keywords
namespace CMD {
    const string
            POLYGON = "polygon",
            PRINT = "print",
            AREA = "area",
            PERIMETER = "perimeter",
            VERTICES = "vertices",
            CENTROID = "centroid",
            SETCOL = "setcol",
            INTERSECTION = "intersection",
            UNION = "union",
            INSIDE = "inside",
            BBOX = "bbox",
            SAVE = "save",
            LOAD = "load",
            DRAW = "draw";
}

const string OUT_DIR = "out/";


// ---------------------------------------

// Gets polygon with ID `id` in `polygons`; throws `UndefinedID` if nonexistent
const ConvexPolygon &getPolygon(const string &id, const PolygonMap &polygons);
ConvexPolygon &getPolygon(const string &id, PolygonMap &polygons);

// Reads a sequence of points from `is` and saves a new polygon from it in `polygons`
void readAndSavePolygon(istream &is, PolygonMap &polygons);

// Print polygon to an output stream in plain format
void printPolygon(const string &id, const ConvexPolygon &pol, ostream &os = cout);

// Save a list of polygons in a text file
void save(const string &file, const vector<string> &polygonIDs, const PolygonMap &polygons);

// Load polygons from text file
void load(const string &file, PolygonMap &polygons);



#endif //CONVEXPOLYGONS_COMMANDS_H
