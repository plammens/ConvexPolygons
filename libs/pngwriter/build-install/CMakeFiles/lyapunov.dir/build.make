# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter/build-install

# Include any dependencies generated for this target.
include CMakeFiles/lyapunov.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lyapunov.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lyapunov.dir/flags.make

CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o: CMakeFiles/lyapunov.dir/flags.make
CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o: ../examples/lyapunov.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter/build-install/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o"
	/usr/bin/c++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o -c /cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter/examples/lyapunov.cc

CMakeFiles/lyapunov.dir/examples/lyapunov.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lyapunov.dir/examples/lyapunov.cc.i"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter/examples/lyapunov.cc > CMakeFiles/lyapunov.dir/examples/lyapunov.cc.i

CMakeFiles/lyapunov.dir/examples/lyapunov.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lyapunov.dir/examples/lyapunov.cc.s"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter/examples/lyapunov.cc -o CMakeFiles/lyapunov.dir/examples/lyapunov.cc.s

CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o.requires:

.PHONY : CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o.requires

CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o.provides: CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o.requires
	$(MAKE) -f CMakeFiles/lyapunov.dir/build.make CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o.provides.build
.PHONY : CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o.provides

CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o.provides.build: CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o


# Object files for target lyapunov
lyapunov_OBJECTS = \
"CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o"

# External object files for target lyapunov
lyapunov_EXTERNAL_OBJECTS =

lyapunov.exe: CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o
lyapunov.exe: CMakeFiles/lyapunov.dir/build.make
lyapunov.exe: libPNGwriter.dll.a
lyapunov.exe: /usr/lib/libpng.dll.a
lyapunov.exe: /usr/lib/libz.dll.a
lyapunov.exe: CMakeFiles/lyapunov.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter/build-install/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lyapunov.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lyapunov.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lyapunov.dir/build: lyapunov.exe

.PHONY : CMakeFiles/lyapunov.dir/build

CMakeFiles/lyapunov.dir/requires: CMakeFiles/lyapunov.dir/examples/lyapunov.cc.o.requires

.PHONY : CMakeFiles/lyapunov.dir/requires

CMakeFiles/lyapunov.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lyapunov.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lyapunov.dir/clean

CMakeFiles/lyapunov.dir/depend:
	cd /cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter/build-install && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter /cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter /cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter/build-install /cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter/build-install /cygdrive/c/Users/Paolo/Code/CLionProjects/convex-polygons/libs/pngwriter/build-install/CMakeFiles/lyapunov.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lyapunov.dir/depend

