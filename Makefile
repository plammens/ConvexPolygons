### Macros ###

CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2

## Directory names (for source, binaries, header and object files) ##
INCLUDE_DIR = include
SRC_DIR = src
CLASS_SUBDIR = class
BIN_DIR = bin
MAIN = main
OBJ_DIR = obj
OUT_DIR = out

## Directory search paths
vpath %.h $(INCLUDE_DIR)
vpath %.h $(INCLUDE_DIR)/$(CLASS_SUBDIR)
vpath %.cc $(SRC_DIR)
vpath %.cc $(SRC_DIR)/$(CLASS_SUBDIR)

## Auto-detected names of header/source pairs (assuming same name): ##
module_sources = $(wildcard $(SRC_DIR)/*.cc $(SRC_DIR)/$(CLASS_SUBDIR)/*.cc)
module_headers = $(patsubst $(SRC_DIR)/%.cc,$(INCLUDE_DIR)%.h, $(module_sources))
module_objects = $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o, $(module_sources))

all_headers = $(wildcard $(INCLUDE_DIR)/*.h $(INCLUDE_DIR)/$(CLASS_SUBDIR)/*.h)


### Rules ###

.PHONY: all clean clean_out run test

all: $(BIN_DIR)/$(MAIN)

clean: clean_out
	rm -r -f $(BIN_DIR) $(OBJ_DIR)

clean_out:
	rm -f $(OUT_DIR)/*

run: all
	@printf "\e[1mExecuting main program... \n\n\e[0m"
	@bin/main

test:
	$(info [$(all_headers)])



## Non-phony ##

# This rule links all object files together and outputs the main executable.
$(BIN_DIR)/$(MAIN): $(module_objects) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(CXXFLAGS)

# This rule compiles source files into their corresponding object file.
$(OBJ_DIR)/%.o: %.cc $(all_headers) | $(OBJ_DIR) $(OBJ_DIR)/$(CLASS_SUBDIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)


# Create binary file directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Create object file directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create class subdirectory in `objects` directory
$(OBJ_DIR)/$(CLASS_SUBDIR): $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(CLASS_SUBDIR)
