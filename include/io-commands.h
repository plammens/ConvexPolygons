/// @file
/// Input-output operations for the polygon calculator

#ifndef CONVEXPOLYGONS_COMMANDS_H
#define CONVEXPOLYGONS_COMMANDS_H

#include <iostream>
#include "details/polygonmap.h"
#include "details/range.h"


//-------- IO COMMANDS --------//

/**
 * Reads an ID and a sequence of points from an input stream, from which a polygon is
 * constructed an saved in a map.
 * @param[in] is  input stream
 * @param[out] polygonMap  map in which to save the new polygon
 */
void readPolygon(std::istream &is, PolygonMap &polygonMap);


/// Same as readAndSavePolygon(std::istream &, PolygonMap &), but without reading an ID first
/// @param[in] id  `id` with which to save the polygon
void readPolygon(std::istream &is, PolygonMap &polygons, const std::string &id);


/**
 * Print polygon to an output stream in plain format.
 * The polygon is formatted as its ID followed by a sequence of space-separated `x y`
 * coordinates with 3 digit precision.
 *
 * @param[in] id  ID of the polygon
 * @param[in] pol  polygon to print
 * @param[out] os  output stream to which the polygon has to be written
 */
void printPolygon(const std::string &id, const ConvexPolygon &pol, std::ostream &os = std::cout);


/**
 * Print polygon to an output stream in a better format.
 * The polygon is formatted as its ID followed by a sequence of `(x, y)`
 * coordinates with 3 digit precision.
 *
 * @param[in] id  ID of the polygon
 * @param[in] pol  polygon to print
 * @param[out] os  output stream to which the polygon has to be written
 */
void prettyPrint(const std::string &id, const ConvexPolygon &pol, std::ostream &os = std::cout);


/**
 * Lists to standard output the current identifiers in use.
 * @param[in] polygonMap  map to be listed
 */
void list(const PolygonMap &polygonMap);


/**
 * Save a list of polygons in a text file. Uses the format described by printPolygon().
 *
 * @param[out] file  file path to which the polygons are to be saved
 * @param[in] polygonIDs  IDs of the polygons to be saved
 * @param[in] polygonMap map where the polygons are contained
 *
 * @pre `file` is a valid file path that can be written to
 * @throws error::IOError if the file couldn't be opened for writing
 */
void save(const std::string &file, const std::vector<std::string> &polygonIDs, const PolygonMap &polygonMap);


/**
 * Loads polygons from a text file into a map. Reads the format produced by save().
 * @param[in] file  file path from which the polygons are to be read
 * @param[out] polygons  polygon map into which polygons are to be loaded
 *
 * @pre `file` is a valid file path that can be read as text
 * @throws error::IOError if the file couldn't be opened for reading as text
 */
void load(const std::string &file, PolygonMap &polygons);


/**
 * Parses commands from a file as if it were standard input.
 *
 * @param[in] file  file from which to read commands
 * @param[in, out] polygonMap  map of polygons with which to execute the commands
 * read from the file
 * @param silent  if set to `true`, the standard output of commands read from
 * the file won't be echoed (although errors will still be shown)
 */
void include(const std::string &file, PolygonMap &polygonMap, bool silent = false);



//-------- GET POLYGON --------//

/**
 * Gets polygon with ID `id` in `polygons`
 * @param id  identifier of the polygon
 * @param polygonMap  map from which to retrieve the polygon with ID `id`
 * @return reference to the polygon with ID `id`
 * @throws error::UndefinedID if no polygon has been assigned yet to `id`
 */
const ConvexPolygon &getPolygon(const std::string &id, const PolygonMap &polygonMap);

/// Non-const version of getPolygon(const std::string &, const PolygonMap &)
ConvexPolygon &getPolygon(const std::string &id, PolygonMap &polygons);


/**
 * Lazily gets the polygon with ID `id` for each `id` in a vector of strings.
 *
 * @param polygonIDs  IDs to retrieve
 * @param polygons
 * @return a (non-evaluated) range of polygons corresponding to each of the `id`s
 * (in the same order)
 *
 * @note Since the returned range is lazy-evaluated, it may be that no exception is thrown
 * when calling this function (e.g., an error::UndefinedID), but it may be
 * thrown later when trying to access the contents of the range.
 */
ConstRange<ConvexPolygon> getPolygons(const std::vector<std::string> &polygonIDs, const PolygonMap &polygonMap);


#endif //CONVEXPOLYGONS_COMMANDS_H
