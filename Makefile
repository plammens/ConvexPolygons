### Global constants ###

## Directory names (for source, binaries, headers, objects...) ##

INCLUDE_DIR = include
SRC_DIR = src
CLASS_SUBDIR = class
LIB_ROOT_DIR = libs
TEST_DIR = test

BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
OBJ_DIR = $(BUILD_DIR)/obj
DEP_DIR = $(BUILD_DIR)/depend
LIB_INCLUDE_DIR = $(LIB_ROOT_DIR)/include
LIB_FILE_DIR = $(LIB_ROOT_DIR)/lib

# dircetory for program's output files:
OUT_DIR = out

# name of main program:
MAIN_NAME = main
MAIN_EXE = $(BIN_DIR)/$(MAIN_NAME).x# output path for main program

## Compiler options ##
CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2 -D NO_FREETYPE
CXX_COMPILE_FLAGS = $(CXXFLAGS) -I $(INCLUDE_DIR) -I $(LIB_INCLUDE_DIR)
CXX_LINK_FLAGS = $(CXXFLAGS) -L $(LIB_FILE_DIR) -l PNGwriter -l png


### Auto-detected files and paths ###

## Directory search paths
vpath %.h $(shell find $(INCLUDE_DIR) -type d)
vpath %.cc $(shell find $(SRC_DIR) -type d)

## Auto-detected names of header/source pairs (assuming same name): ##
sources = $(shell find $(SRC_DIR) -type f -name '*.cc')
objects = $(patsubst %.cc,$(OBJ_DIR)/%.o, $(notdir $(sources)))
depends = $(patsubst $(OBJ_DIR)/%.o,$(DEP_DIR)/%.d,$(objects))
# ^^^ dependency files for automatic Makefile rule prerequisites


## Tests ##

TEST_SUITE = doctest
TEST_NAME = test# name of test executable
TEST_EXE = $(BIN_DIR)/$(TEST_NAME).x# output path for test executable

CXX_TEST_FLAGS = $(CXXFLAGS) -I $(TEST_DIR)/$(INCLUDE_DIR)

tests = $(shell find $(TEST_DIR)/$(SRC_DIR) -type f -name '*.cc')



### Rules ###

.PHONY: all compile run clean clean_build clean_out test libs

all: libs $(MAIN_EXE)

compile: $(objects)

run: all
	@printf "\e[1mExecuting main program...\e[0m ($(MAIN_EXE))\n\n"
	@$(MAIN_EXE)
	@echo

clean: clean_build clean_out

clean_build:
	rm -rf ./$(BUILD_DIR)

clean_out:
	rm -rf ./$(OUT_DIR)

test: compile $(TEST_EXE)
	@printf "\e[1mStarting $(TEST_SUITE)...\e[0m ($(TEST_EXE))\n\n"
	@$(TEST_EXE)
	@echo

libs: $(LIB_FILE_DIR)/libPNGwriter.a


## Non-phony ##

-include $(depends)  # include dependecy relationships

# This rule links all object files together and outputs the main executable.
$(MAIN_EXE): $(objects) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(CXX_LINK_FLAGS)

# This rule compiles source files into their corresponding object file.
# As a side effect of compilation we generate a dependency file (with the `-MMD -MF` flags)
$(OBJ_DIR)/%.o: %.cc | $(OBJ_DIR) $(DEP_DIR)
	$(CXX) -c $< -o $@ $(CXX_COMPILE_FLAGS) -MMD -MF $(patsubst $(OBJ_DIR)/%.o,$(DEP_DIR)/%.d,$@)


# Create build directories if nonexistent:
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(DEP_DIR):
	mkdir -p $(DEP_DIR)


$(LIB_FILE_DIR)/libPNGwriter.a:
	cmake $(LIB_ROOT_DIR)/pngwriter/CMakeLists.txt -DPNGwriter_USE_FREETYPE=OFF -DCMAKE_INSTALL_PREFIX=$(LIB_ROOT_DIR)
	make -C $(LIB_ROOT_DIR)/pngwriter
	make -C $(LIB_ROOT_DIR)/pngwriter install



## Test rules ##


$(TEST_EXE): $(tests) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(CXX_TEST_FLAGS)

