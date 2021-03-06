#include "details/handlers.h"

#include <cassert>
#include <iostream>
#include "io-commands.h"  // save, load, list...
#include "draw.h"  // draw
#include "errors.h"
#include "details/utils.h"  // getArgs


//-------- INTERNAL --------//

//---- Console messages ----//

inline
void printOk() {
    std::cout << "ok" << std::endl;
}


inline
void printError(const std::string &error) {
    // \e[31;1m is the ANSI escape sequence for bright red text
    std::cerr << "\e[31;1m" << "error: " << error << "\e[0m" << std::endl;
}

inline
void printWarning(const std::string &warning) {
    // \e[33m is the ANSI escape sequence for yellow text
    std::cerr << "\e[33m" << "warning: " << warning << "\e[0m" << std::endl;
}



//-------- EXPOSED FUNCTIONS --------//

void handleIDManagement(const std::string &keyword, std::istream &argStream, PolygonMap &polygons) {
    std::string id;
    getArgs(argStream, id);

    if (keyword == cmd::POLYGON) readPolygon(argStream, polygons, id);
    else if (keyword == cmd::DELETE) polygons.erase(id);
    else assert(false);

    printOk();
}


void handlePolygonMethod(const std::string &keyword, std::istream &argStream, PolygonMap &polygons) {
    std::string id;
    getArgs(argStream, id);
    ConvexPolygon &pol = getPolygon(id, polygons);  // throws `UndefinedID` if nonexistent

    if      (keyword == cmd::PRINT) printPolygon(id, pol);
    else if (keyword == cmd::PRETTYPRINT) prettyPrint(id, pol);
    else if (keyword == cmd::AREA) std::cout << pol.area() << std::endl;
    else if (keyword == cmd::PERIMETER) std::cout << pol.perimeter() << std::endl;
    else if (keyword == cmd::VERTICES) std::cout << pol.vertexCount() << std::endl;
    else if (keyword == cmd::CENTROID) std::cout << pol.centroid() << std::endl;
    else if (keyword == cmd::SETCOL) {
        double r, g, b;
        getArgs(argStream, r, g, b);
        pol.setColor(RGBColor{r, g, b});
        printOk();
    }
    else assert(false);  // Shouldn't get here
}


void handleBinaryOperation(const std::string &keyword, std::istream &argStream, PolygonMap &polygons) {
    std::string id1, id2, id3;
    getArgs(argStream, id1, id2);
    argStream >> id3;  // no exception if not available

    // arguments to the operation:
    const ConvexPolygon &p1 = getPolygon(id3.empty() ? id1 : id2, polygons);
    const ConvexPolygon &p2 = getPolygon(id3.empty() ? id2 : id3, polygons);

    if      (keyword == cmd::INSIDE) {
        std::cout << (isInside(p1, p2) ? "yes" : "no") << std::endl;
        return;
    }
    else if (keyword == cmd::UNION) polygons[id1] = convexUnion(p1, p2);
    else if (keyword == cmd::INTERSECTION) polygons[id1] = intersection(p1, p2);
    else assert(false);

    printOk();
}


void handleNAryOperation(const std::string &keyword, std::istream &argStream, PolygonMap &polygons) {
    std::string id;
    getArgs(argStream, id);
    std::vector<std::string> polIDs = readVector<std::string>(argStream);

    if (keyword == cmd::BBOX)
        polygons[id] = boundingBox(getPolygons(polIDs, polygons));
    else assert(false);

    printOk();
}


void handleIOCommand(const std::string &keyword, std::istream &argStream, PolygonMap &polygons) {
    std::string file;
    argStream >> file;
    if (file.empty()) throw error::SyntaxError("no file specified");
    prefixPath(file, io::OUT_DIR);  // prefix with output directory
    std::vector<std::string> polygonIDs = readVector<std::string>(argStream);

    if (keyword == cmd::SAVE) save(file, polygonIDs, polygons);
    else if (keyword == cmd::LOAD) load(file, polygons);
    else if (keyword == cmd::DRAW) draw(file, getPolygons(polygonIDs, polygons));
    else if (keyword == cmd::PAINT) draw(file, getPolygons(polygonIDs, polygons), true);
    else if (keyword == cmd::INCLUDE) include(file, polygons);
    else assert(false); // Shouldn't get here

    printOk();
}


void handleNullaryCommand(const std::string &keyword, std::istream &argStream, PolygonMap &polygons) {
    if (keyword == cmd::LIST) list(polygons);
    else assert(false); // Shouldn't get here
}

// -------------------


CommandHandler getCommandHandler(const std::string &keyword) {
    auto it = cmdHandlerMap.find(keyword);
    if (it == cmdHandlerMap.end()) throw error::UnknownCommand(keyword);
    return it->second;
}


// Check whether command is valid and run corresponding handler
void parseCommand(const std::string &command, PolygonMap &polygonMap) {
    if (command.empty()) return;  // ignore empty lines

    try {
        std::istringstream iss(command);
        std::string keyword;
        iss >> keyword;
        if (keyword[0] == '#') { std::cout << '#' << std::endl; return; }  // comments

        // Get appropriate handler: (may throw `UnknownCommand`)
        CommandHandler handler = getCommandHandler(keyword);
        handler(keyword, iss, polygonMap);
        if (not (iss >> std::ws).eof()) throw error::UnusedArgument();  // check unused arguments

    } catch (error::Error &error) {
        printError(error.what());
    } catch (error::Warning &warning) {
        printWarning(warning.what());
    }
}
