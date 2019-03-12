### Macros ###

CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2

## Directory names (for source, binaries, header and object files) ##
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include
OBJ_DIR = obj

## Name of main program and dependencies ##
# This is the only part that needs to be edited. Here we assume that
# source files (e.g. `foo.cpp`) and header files (e.g. `foo.h`) share
# the same name (besides the extension).
MAIN = main
DEPENDENCIES = utils Vector2D Point ConvexPolygon

## Header and object file paths ##
HEADERS = $(patsubst %, $(INCLUDE_DIR)/%.h, $(DEPENDENCIES))
OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(MAIN) $(DEPENDENCIES))



### Rules ###

all: $(BIN_DIR)/$(MAIN)

clean:
	rm -r -f $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean


## Non-phony ##

# This rule links all object files together and outputs the main executable.
$(BIN_DIR)/$(MAIN): $(OBJ) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(CXXFLAGS)

# This rule compiles source files into their corresponding object file.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(DEPS) | $(OBJ_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Create binary file directory if it doesn't exist
$(BIN_DIR):
	mkdir $(BIN_DIR)

# Create object file directory if it doesn't exist
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

