# TODO: suffix awareness (.cc vs .cpp) 
# TODO: test_impl file flexibility (test/src/main.cpp)
# TODO: separate library section (append instead of embed)


############################# User-defined constants ################################

##### Directory names #####

INCLUDE_DIR := include
SRC_DIR := src
CLASS_SUBDIR := class
LIB_ROOT_DIR := libs
TEST_DIR := test
DOCS_DIR := docs
EXAMPLES_DIR = examples

# directory for build files (binaries, object files, etc.):
BUILD_DIR := build

# output root directory for main program:
OUT_DIR := out



##### Configuration #####

# directory to find any additional static library files (.a):
USER_LIB_DIR := $(HOME)/libs/lib

# browser (for viewing html docs):
BROWSER := firefox

# name of main executable:
MAIN_NAME := main

# test suite and test executable name:
TEST_SUITE := doctest
TEST_NAME := test

# Python interpreter
PYTHON := python3




############################# Macros ################################


##### Directory names #####

TEST_TEXT_DIR = $(TEST_DIR)/text
BIN_DIR = $(BUILD_DIR)/bin
OBJ_DIR = $(BUILD_DIR)/obj

DEP_DIR = $(BUILD_DIR)/depend
LIB_INCLUDE_DIR = $(LIB_ROOT_DIR)/include
LIB_FILE_DIR = $(LIB_ROOT_DIR)/lib


##### file paths #####

MAIN_EXE = $(BIN_DIR)/$(MAIN_NAME).x
MAIN_OBJ = $(OBJ_DIR)/$(MAIN_NAME).o

TEST_EXE = $(BIN_DIR)/$(TEST_NAME).x



##### Compiler options and flags ######

CXX = g++
CXXFLAGS = -std=c++11 -O2 -D NO_FREETYPE

CXX_COMPILE_FLAGS = $(CXXFLAGS) -I $(INCLUDE_DIR) -I $(LIB_INCLUDE_DIR)
CXX_LINK_FLAGS = $(CXXFLAGS) -L $(LIB_FILE_DIR) -L $(USER_LIB_DIR) -l PNGwriter -l png

CXX_TEST_COMPILE_FLAGS = $(CXX_COMPILE_FLAGS) -I $(TEST_DIR)/$(INCLUDE_DIR) -Og
CXX_TEST_LINK_FLAGS = $(CXX_LINK_FLAGS) -Og


##### Auto-detected files and paths #####

# Directory search paths:
vpath %.h $(shell find $(INCLUDE_DIR) -type d)
vpath %.cc $(shell find $(SRC_DIR) -type d)
vpath test%.cc $(shell find $(TEST_DIR)/$(SRC_DIR) -type d)

# sources and objects:
sources = $(shell find $(SRC_DIR) -type f -name '*.cc' ! -name '$(MAIN_NAME)*')  # sources excluding main
objects = $(patsubst %.cc,$(OBJ_DIR)/%.o, $(notdir $(sources)))  # object files

# test sources (prefixed with 'test'):
test_sources = $(shell find $(TEST_DIR)/$(SRC_DIR) -type f -name 'test*.cc')
test_objects = $(patsubst %.cc,$(OBJ_DIR)/%.o, $(notdir $(test_sources)))

# dependency files for automatic Makefile rule prerequisites
depends = $(patsubst $(OBJ_DIR)/%.o,$(DEP_DIR)/%.d,$(objects) $(test_objects))

# example scripts:
example_scripts = $(shell find $(EXAMPLES_DIR) -type f -name '*.sh')



################################## Rules ######################################

############### Phony rules ###############

.PHONY: all build build-test debug libs run test \
		clean clean-build clean-out docs view-docs examples \
		.pre-build .pre-lib .pre-build-test


all: build build-test examples


build: .pre-build $(MAIN_EXE)
	@printf "\e[1mDone building main.\e[0m\n\n"

build-test: debug .pre-build-test $(TEST_EXE) $(TEST_DIR)/text
	$(PYTHON) test/generator.py
	@printf "\e[1mDone building tests.\e[0m\n\n"

debug: CXXFLAGS += -Wall -Og
debug: build


libs: $(LIB_FILE_DIR)/libPNGwriter.a | .pre-lib
	@printf "\e[1mDone building libs.\e[0m\n\n"


run: build $(OUT_DIR)
	@echo
	@printf "\e[1mExecuting main program...\e[0m ($(MAIN_EXE))\n\n"
	@$(MAIN_EXE)
	@echo

test: build-test
	@echo
	@printf "\e[1mStarting $(TEST_SUITE)...\e[0m ($(TEST_EXE) $(ARGS))\n\n"
	@$(TEST_EXE) $(ARGS)
	@echo


clean: clean-build clean-out

clean-build:
	rm -rf ./$(BUILD_DIR)

clean-out:
	rm -rf ./$(OUT_DIR)


docs:
	doxygen $(DOCS_DIR)/Doxyfile

view-docs:
	$(BROWSER) $(DOCS_DIR)/html/index.html &

examples: build $(OUT_DIR)
	@for script in $(example_scripts) ; do \
		printf "\e[1mRunning $$script...\e[0m\n" ; \
		sh $$script ; \
		echo ; \
	done


# Just some text:

.pre-build:
	@printf "\e[1mBuilding main program...\e[0m\n"

.pre-lib:
	@printf "\e[1mBuilding libraries...\e[0m\n"

.pre-build-test:
	@printf "\e[1mBuilding tests...\e[0m\n"



########## Main project rules #############

-include $(depends)  # include dependecy relationships

# This rule links all object files together and outputs the main executable.
$(MAIN_EXE): $(objects) $(MAIN_OBJ) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(CXX_LINK_FLAGS)

# This rule compiles source files into their corresponding object file.
# As a side effect of compilation we generate a dependency file readable
# by make (with the `-MMD -MF` flags)
$(OBJ_DIR)/%.o: %.cc | $(OBJ_DIR) $(DEP_DIR)
	$(CXX) -c $< -o $@ $(CXX_COMPILE_FLAGS) -MMD -MF $(patsubst $(OBJ_DIR)/%.o,$(DEP_DIR)/%.d,$@)


# Create build directories if nonexistent:

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(DEP_DIR):
	mkdir -p $(DEP_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)


############## Library rules ##############

# Build PNGwriter library from source:
$(LIB_FILE_DIR)/libPNGwriter.a:
	mkdir -p $(LIB_ROOT_DIR)/pngwriter-build-install
	cd $(LIB_ROOT_DIR)/pngwriter-build-install && \
		cmake ../pngwriter/ -DPNGwriter_USE_FREETYPE=OFF -DCMAKE_INSTALL_PREFIX=../ && \
		echo && $(PYTHON) ../pngwriter_fix.py && echo && \
		make install --no-print-directory



############### Test rules ################

# Compile and link all test objects (together with the project's objects), outputting an executable:
$(TEST_EXE): $(objects) $(test_objects) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(CXX_TEST_LINK_FLAGS)

# This rule compiles test source files into their corresponding object file.
# As a side effect of compilation we generate a dependency file.
$(OBJ_DIR)/test%.o: test%.cc | $(OBJ_DIR) $(DEP_DIR)
	$(CXX) -c $< -o $@ $(CXX_TEST_COMPILE_FLAGS) -MMD -MF $(patsubst $(OBJ_DIR)/%.o,$(DEP_DIR)/%.d,$@)


$(TEST_DIR)/text:
	mkdir -p $(TEST_DIR)/text

