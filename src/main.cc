#include <iostream>
#include <sstream>
#include "../include/commands.h"
#include "../include/handlers.h"
#include "../include/errors.h"


using namespace std;


// Check whether command is valid and run corresponding handler
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
    } catch (SyntaxError &) {
        printError("invalid command syntax");
    } catch (UndefinedID &) {
        printError("undefined ID");
    } catch (IOError &) {
        printError("unable to access file");
    }
}

// -----------------------------------------------------------------


int main() {
    PolygonMap polygons;
    string command;
    while (getline(cin, command)) parseCommand(command, polygons);
}
