// Program's main entry point
// TODO: remove helper functions from headers
// TODO: unify comment separators
// TODO: final rearrange
// TODO: docs & doxygen
// TODO: remove using std
// TODO: impl folder, hide utils
// TODO: boost or not?

#include <iostream>
#include "details/handlers.h"


int main() {
    PolygonMap polygons;
    std::string command;
    while (getline(std::cin, command)) parseCommand(command, polygons);
}
