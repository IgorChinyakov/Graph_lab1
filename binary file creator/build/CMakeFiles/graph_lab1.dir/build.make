# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/chinyakov/CLionProjects/graph_lab_bin_create

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chinyakov/CLionProjects/graph_lab_bin_create/build

# Include any dependencies generated for this target.
include CMakeFiles/graph_lab1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/graph_lab1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/graph_lab1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/graph_lab1.dir/flags.make

CMakeFiles/graph_lab1.dir/main.cpp.o: CMakeFiles/graph_lab1.dir/flags.make
CMakeFiles/graph_lab1.dir/main.cpp.o: /home/chinyakov/CLionProjects/graph_lab_bin_create/main.cpp
CMakeFiles/graph_lab1.dir/main.cpp.o: CMakeFiles/graph_lab1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chinyakov/CLionProjects/graph_lab_bin_create/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/graph_lab1.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/graph_lab1.dir/main.cpp.o -MF CMakeFiles/graph_lab1.dir/main.cpp.o.d -o CMakeFiles/graph_lab1.dir/main.cpp.o -c /home/chinyakov/CLionProjects/graph_lab_bin_create/main.cpp

CMakeFiles/graph_lab1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/graph_lab1.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chinyakov/CLionProjects/graph_lab_bin_create/main.cpp > CMakeFiles/graph_lab1.dir/main.cpp.i

CMakeFiles/graph_lab1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/graph_lab1.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chinyakov/CLionProjects/graph_lab_bin_create/main.cpp -o CMakeFiles/graph_lab1.dir/main.cpp.s

# Object files for target graph_lab1
graph_lab1_OBJECTS = \
"CMakeFiles/graph_lab1.dir/main.cpp.o"

# External object files for target graph_lab1
graph_lab1_EXTERNAL_OBJECTS =

graph_lab1: CMakeFiles/graph_lab1.dir/main.cpp.o
graph_lab1: CMakeFiles/graph_lab1.dir/build.make
graph_lab1: CMakeFiles/graph_lab1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/chinyakov/CLionProjects/graph_lab_bin_create/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable graph_lab1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graph_lab1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/graph_lab1.dir/build: graph_lab1
.PHONY : CMakeFiles/graph_lab1.dir/build

CMakeFiles/graph_lab1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/graph_lab1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/graph_lab1.dir/clean

CMakeFiles/graph_lab1.dir/depend:
	cd /home/chinyakov/CLionProjects/graph_lab_bin_create/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chinyakov/CLionProjects/graph_lab_bin_create /home/chinyakov/CLionProjects/graph_lab_bin_create /home/chinyakov/CLionProjects/graph_lab_bin_create/build /home/chinyakov/CLionProjects/graph_lab_bin_create/build /home/chinyakov/CLionProjects/graph_lab_bin_create/build/CMakeFiles/graph_lab1.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/graph_lab1.dir/depend
