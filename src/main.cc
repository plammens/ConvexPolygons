// Program's main entry point
// TODO: remove helper functions from headers
// TODO: unify comment separators
// TODO: final rearrange
// TODO: docs & doxygen
// TODO: boost or not?
// TODO: document special cases

#include <iostream>
#include "details/handlers.h"


int main() {
    PolygonMap polygons;
    std::string command;
    while (getline(std::cin, command)) parseCommand(command, polygons);
}
