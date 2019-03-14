#ifndef CONVEXPOLYGONS_COMMANDS_H
#define CONVEXPOLYGONS_COMMANDS_H

#include <string>
#include <map>
#include "ConvexPolygon.h"


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

// Reads a sequence of points from `is` and saves a new polygon from it in `polygons`
void readAndSavePolygon(istream &is, PolygonMap &polygons);

// Save a list of polygons in a text file
void save(const string &file, const vector<string> &polygonIDs, const PolygonMap &polygons);

// Load polygons from text file
void load(const string &file, PolygonMap &polygons);


#endif //CONVEXPOLYGONS_COMMANDS_H
