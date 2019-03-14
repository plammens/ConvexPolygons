#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include "../include/ConvexPolygon.h"
#include "../include/commands.h"


using namespace std;



// ------------------------------------------------


// Check whether command is valid and run corresponding subroutine
void parseCommand(const string &command, PolygonMap &polygons) {
    if (command.empty()) return;  // ignore empty lines
    try {

        istringstream iss(command);
        string keyword;
        iss >> keyword;
        // Get appropriate handler: (may throw `UnrecognizedCommand`)
        CommandHandler handler = getCommandHandler(keyword);
        handler(keyword, iss, polygons);

    } catch (UnrecognizedCommand &) {
        printError("unrecognized command");
    } catch (out_of_range &) {
        printError("undefined ID");
    } catch (IOError &) {
        printError("unable to access file");
    } catch (SyntaxError &) {
        printError("invalid command syntax");
    }
}

// ------------------------------------------------


int main() {
    PolygonMap polygons;
    string command;
    while (getline(cin, command)) parseCommand(command, polygons);
}
