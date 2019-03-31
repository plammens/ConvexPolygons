/// @file
/// Alias for a ID-to-polygon associative container.

#ifndef CONVEXPOLYGONS_POLYGONMAP_H
#define CONVEXPOLYGONS_POLYGONMAP_H

#include <map>
#include <string>
#include "class/ConvexPolygon.h"


/// Alias for an associative container mapping identifiers (strings) to polygons
typedef std::map<std::string, ConvexPolygon> PolygonMap;


#endif //CONVEXPOLYGONS_POLYGONMAP_H
