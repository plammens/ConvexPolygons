// Program's main entry point
// TODO: remove helper functions from headers
// TODO: unify comment separators
// TODO: final rearrange
// TODO: docs & doxygen
// TODO: remove using std
// TODO: impl folder, hide utils
// TODO: boost or not?

#include <iostream>
#include <sstream>
#include "class/ConvexPolygon.h"
#include "details/handlers.h"
#include "errors.h"


using namespace std;


// Check whether command is valid and run corresponding handler
void parseCommand(const string &command, PolygonMap &polygons) {
    if (command.empty()) return;  // ignore empty lines

    try {
        istringstream iss(command);
        string keyword;
        iss >> keyword;
        if (keyword[0] == '#') { cout << '#' << endl; return; }  // comments

        // Get appropriate handler: (may throw `UnknownCommand`)
        CommandHandler handler = getCommandHandler(keyword);
        handler(keyword, iss, polygons);
        if (not (iss >> ws).eof()) throw UnusedArgument();  // check unused arguments

    } catch (Error &error) {
        printError(error.what());
    } catch (Warning &warning) {
        printWarning(warning.what());
    }
}

// -----------------------------------------------------------------


int main() {
    PolygonMap polygons;
    string command;
    while (getline(cin, command)) parseCommand(command, polygons);
}
