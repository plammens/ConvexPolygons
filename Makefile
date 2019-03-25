############################# Global variables ################################

##### Directory names #####

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


##### Executable names #####

# name of main program:
MAIN_NAME = main
MAIN_EXE = $(BIN_DIR)/$(MAIN_NAME).x# output path for main program
MAIN_OBJ = $(OBJ_DIR)/$(MAIN_NAME).o

TEST_SUITE = doctest
TEST_NAME = test
TEST_EXE = $(BIN_DIR)/$(TEST_NAME).x


##### Compiler options and flags ######

CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2 -D NO_FREETYPE

CXX_COMPILE_FLAGS = $(CXXFLAGS) -I $(INCLUDE_DIR) -I $(LIB_INCLUDE_DIR)
CXX_LINK_FLAGS = $(CXXFLAGS) -L $(LIB_FILE_DIR) -l PNGwriter -l png

CXX_TEST_COMPILE_FLAGS = $(CXX_COMPILE_FLAGS) -I $(TEST_DIR)/$(INCLUDE_DIR) -O0
CXX_TEST_LINK_FLAGS = $(CXX_LINK_FLAGS) -O0


##### Auto-detected files and paths #####

## Directory search paths ##
vpath %.h $(shell find $(INCLUDE_DIR) -type d)
vpath %.cc $(shell find $(SRC_DIR) -type d)
vpath test%.cc $(shell find $(TEST_DIR)/$(SRC_DIR) -type d)

## Auto-detected source files: ##
sources = $(shell find $(SRC_DIR) -type f -name '*.cc' ! -name '$(MAIN_NAME)*')  # sources excluding main
objects = $(patsubst %.cc,$(OBJ_DIR)/%.o, $(notdir $(sources)))  # object files

# test sources (prefixed with 'test')
test_sources = $(shell find $(TEST_DIR)/$(SRC_DIR) -type f -name 'test*.cc')  # all test source files
test_objects = $(patsubst %.cc,$(OBJ_DIR)/%.o, $(notdir $(test_sources)))  # all test object files

# dependency files for automatic Makefile rule prerequisites
depends = $(patsubst $(OBJ_DIR)/%.o,$(DEP_DIR)/%.d,$(objects) $(test_objects))



################################## Rules ######################################

############### Phony rules ###############

.PHONY: all build run clean clean-build clean-out test libs \
		.pre-build .pre-lib .pre-build-test


all: libs build build-test


build: .pre-build $(MAIN_EXE)
	@printf "\e[1mDone building main.\e[0m\n\n"

libs: .pre-lib $(LIB_FILE_DIR)/libPNGwriter.a
	@printf "\e[1mDone building libs.\e[0m\n\n"

build-test: build .pre-build-test $(TEST_EXE)
	@printf "\e[1mDone building tests.\e[0m\n\n"


run: build
	@echo
	@printf "\e[1mExecuting main program...\e[0m ($(MAIN_EXE))\n\n"
	@$(MAIN_EXE)
	@echo

test: build-test
	@echo
	@printf "\e[1mStarting $(TEST_SUITE)...\e[0m ($(TEST_EXE) $(ARGS))\n\n"
	@$(TEST_EXE) $(ARGS)
	@echo

info:
	$(info $(CXX_TEST_COMPILE_FLAGS))


clean: clean-build clean-out

clean-build:
	rm -rf ./$(BUILD_DIR)

clean-out:
	rm -rf ./$(OUT_DIR)


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



############## Library rules ##############

# Build PNGwriter library from source:
$(LIB_FILE_DIR)/libPNGwriter.a:
	cmake $(LIB_ROOT_DIR)/pngwriter/CMakeLists.txt -DPNGwriter_USE_FREETYPE=OFF -DCMAKE_INSTALL_PREFIX=$(LIB_ROOT_DIR)
	make -C $(LIB_ROOT_DIR)/pngwriter
	make -C $(LIB_ROOT_DIR)/pngwriter install



############### Test rules ################

# Compile and link all test objects (together with the project's objects), outputting an executable:
$(TEST_EXE): $(objects) $(test_objects) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(CXX_TEST_LINK_FLAGS)

# This rule compiles test source files into their corresponding object file.
# As a side effect of compilation we generate a dependency file.
$(OBJ_DIR)/test%.o: test%.cc | $(OBJ_DIR) $(DEP_DIR)
	$(CXX) -c $< -o $@ $(CXX_TEST_COMPILE_FLAGS) -MMD -MF $(patsubst $(OBJ_DIR)/%.o,$(DEP_DIR)/%.d,$@)
