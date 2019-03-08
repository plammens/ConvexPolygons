### Macros ###

CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2

## Directory names (for source, header and object files) ##
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

## Name of main program and dependencies ##
# This is the only part that needs to be edited. Here we assume that
# source files (e.g. `foo.cpp`) and header files (e.g. `foo.h`) share
# the same name (besides the extension).
MAIN = main
DEPENDENCIES = utils GeometricVector Point ConvexPolygon

## Header and object file paths ##
HEADERS = $(patsubst %, $(INCLUDE_DIR)/%.h, $(DEPENDENCIES))
OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(MAIN) $(DEPENDENCIES))



### Rules ###

all: main

clean:
	rm -f main.exe *.o

# This rule links all object files together and outputs an executable.
main: $(OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS)

# This rule compiles source files into their corresponding object file.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CXX) -c $< -o $@ $(CXXFLAGS)
