# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/diego/dati/workspace/oathsworn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/diego/dati/workspace/oathsworn/build

# Include any dependencies generated for this target.
include CMakeFiles/oathsworn.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/oathsworn.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/oathsworn.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/oathsworn.dir/flags.make

CMakeFiles/oathsworn.dir/oathsworn.cpp.o: CMakeFiles/oathsworn.dir/flags.make
CMakeFiles/oathsworn.dir/oathsworn.cpp.o: /home/diego/dati/workspace/oathsworn/oathsworn.cpp
CMakeFiles/oathsworn.dir/oathsworn.cpp.o: CMakeFiles/oathsworn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/diego/dati/workspace/oathsworn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/oathsworn.dir/oathsworn.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/oathsworn.dir/oathsworn.cpp.o -MF CMakeFiles/oathsworn.dir/oathsworn.cpp.o.d -o CMakeFiles/oathsworn.dir/oathsworn.cpp.o -c /home/diego/dati/workspace/oathsworn/oathsworn.cpp

CMakeFiles/oathsworn.dir/oathsworn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/oathsworn.dir/oathsworn.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/diego/dati/workspace/oathsworn/oathsworn.cpp > CMakeFiles/oathsworn.dir/oathsworn.cpp.i

CMakeFiles/oathsworn.dir/oathsworn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/oathsworn.dir/oathsworn.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/diego/dati/workspace/oathsworn/oathsworn.cpp -o CMakeFiles/oathsworn.dir/oathsworn.cpp.s

# Object files for target oathsworn
oathsworn_OBJECTS = \
"CMakeFiles/oathsworn.dir/oathsworn.cpp.o"

# External object files for target oathsworn
oathsworn_EXTERNAL_OBJECTS =

oathsworn: CMakeFiles/oathsworn.dir/oathsworn.cpp.o
oathsworn: CMakeFiles/oathsworn.dir/build.make
oathsworn: CMakeFiles/oathsworn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/diego/dati/workspace/oathsworn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable oathsworn"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/oathsworn.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/oathsworn.dir/build: oathsworn
.PHONY : CMakeFiles/oathsworn.dir/build

CMakeFiles/oathsworn.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/oathsworn.dir/cmake_clean.cmake
.PHONY : CMakeFiles/oathsworn.dir/clean

CMakeFiles/oathsworn.dir/depend:
	cd /home/diego/dati/workspace/oathsworn/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/diego/dati/workspace/oathsworn /home/diego/dati/workspace/oathsworn /home/diego/dati/workspace/oathsworn/build /home/diego/dati/workspace/oathsworn/build /home/diego/dati/workspace/oathsworn/build/CMakeFiles/oathsworn.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/oathsworn.dir/depend
