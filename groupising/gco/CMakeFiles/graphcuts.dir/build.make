# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/sci/projects/neuro/software/cmake-2.8.7-bin/bin/cmake

# The command to remove a file.
RM = /usr/sci/projects/neuro/software/cmake-2.8.7-bin/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/sci/projects/neuro/software/cmake-2.8.7-bin/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sci/weiliu/projects/groupising

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sci/weiliu/projects/groupising

# Include any dependencies generated for this target.
include gco/CMakeFiles/graphcuts.dir/depend.make

# Include the progress variables for this target.
include gco/CMakeFiles/graphcuts.dir/progress.make

# Include the compile flags for this target's objects.
include gco/CMakeFiles/graphcuts.dir/flags.make

gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o: gco/CMakeFiles/graphcuts.dir/flags.make
gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o: gco/GCoptimization.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sci/weiliu/projects/groupising/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/graphcuts.dir/GCoptimization.cpp.o -c /home/sci/weiliu/projects/groupising/gco/GCoptimization.cpp

gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphcuts.dir/GCoptimization.cpp.i"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sci/weiliu/projects/groupising/gco/GCoptimization.cpp > CMakeFiles/graphcuts.dir/GCoptimization.cpp.i

gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphcuts.dir/GCoptimization.cpp.s"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sci/weiliu/projects/groupising/gco/GCoptimization.cpp -o CMakeFiles/graphcuts.dir/GCoptimization.cpp.s

gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o.requires:
.PHONY : gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o.requires

gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o.provides: gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o.requires
	$(MAKE) -f gco/CMakeFiles/graphcuts.dir/build.make gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o.provides.build
.PHONY : gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o.provides

gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o.provides.build: gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o

gco/CMakeFiles/graphcuts.dir/graph.cpp.o: gco/CMakeFiles/graphcuts.dir/flags.make
gco/CMakeFiles/graphcuts.dir/graph.cpp.o: gco/graph.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sci/weiliu/projects/groupising/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object gco/CMakeFiles/graphcuts.dir/graph.cpp.o"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/graphcuts.dir/graph.cpp.o -c /home/sci/weiliu/projects/groupising/gco/graph.cpp

gco/CMakeFiles/graphcuts.dir/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphcuts.dir/graph.cpp.i"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sci/weiliu/projects/groupising/gco/graph.cpp > CMakeFiles/graphcuts.dir/graph.cpp.i

gco/CMakeFiles/graphcuts.dir/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphcuts.dir/graph.cpp.s"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sci/weiliu/projects/groupising/gco/graph.cpp -o CMakeFiles/graphcuts.dir/graph.cpp.s

gco/CMakeFiles/graphcuts.dir/graph.cpp.o.requires:
.PHONY : gco/CMakeFiles/graphcuts.dir/graph.cpp.o.requires

gco/CMakeFiles/graphcuts.dir/graph.cpp.o.provides: gco/CMakeFiles/graphcuts.dir/graph.cpp.o.requires
	$(MAKE) -f gco/CMakeFiles/graphcuts.dir/build.make gco/CMakeFiles/graphcuts.dir/graph.cpp.o.provides.build
.PHONY : gco/CMakeFiles/graphcuts.dir/graph.cpp.o.provides

gco/CMakeFiles/graphcuts.dir/graph.cpp.o.provides.build: gco/CMakeFiles/graphcuts.dir/graph.cpp.o

gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o: gco/CMakeFiles/graphcuts.dir/flags.make
gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o: gco/LinkedBlockList.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sci/weiliu/projects/groupising/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o -c /home/sci/weiliu/projects/groupising/gco/LinkedBlockList.cpp

gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.i"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sci/weiliu/projects/groupising/gco/LinkedBlockList.cpp > CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.i

gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.s"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sci/weiliu/projects/groupising/gco/LinkedBlockList.cpp -o CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.s

gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o.requires:
.PHONY : gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o.requires

gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o.provides: gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o.requires
	$(MAKE) -f gco/CMakeFiles/graphcuts.dir/build.make gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o.provides.build
.PHONY : gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o.provides

gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o.provides.build: gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o

gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o: gco/CMakeFiles/graphcuts.dir/flags.make
gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o: gco/maxflow.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sci/weiliu/projects/groupising/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/graphcuts.dir/maxflow.cpp.o -c /home/sci/weiliu/projects/groupising/gco/maxflow.cpp

gco/CMakeFiles/graphcuts.dir/maxflow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphcuts.dir/maxflow.cpp.i"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sci/weiliu/projects/groupising/gco/maxflow.cpp > CMakeFiles/graphcuts.dir/maxflow.cpp.i

gco/CMakeFiles/graphcuts.dir/maxflow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphcuts.dir/maxflow.cpp.s"
	cd /home/sci/weiliu/projects/groupising/gco && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sci/weiliu/projects/groupising/gco/maxflow.cpp -o CMakeFiles/graphcuts.dir/maxflow.cpp.s

gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o.requires:
.PHONY : gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o.requires

gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o.provides: gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o.requires
	$(MAKE) -f gco/CMakeFiles/graphcuts.dir/build.make gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o.provides.build
.PHONY : gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o.provides

gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o.provides.build: gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o

# Object files for target graphcuts
graphcuts_OBJECTS = \
"CMakeFiles/graphcuts.dir/GCoptimization.cpp.o" \
"CMakeFiles/graphcuts.dir/graph.cpp.o" \
"CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o" \
"CMakeFiles/graphcuts.dir/maxflow.cpp.o"

# External object files for target graphcuts
graphcuts_EXTERNAL_OBJECTS =

gco/libgraphcuts.a: gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o
gco/libgraphcuts.a: gco/CMakeFiles/graphcuts.dir/graph.cpp.o
gco/libgraphcuts.a: gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o
gco/libgraphcuts.a: gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o
gco/libgraphcuts.a: gco/CMakeFiles/graphcuts.dir/build.make
gco/libgraphcuts.a: gco/CMakeFiles/graphcuts.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libgraphcuts.a"
	cd /home/sci/weiliu/projects/groupising/gco && $(CMAKE_COMMAND) -P CMakeFiles/graphcuts.dir/cmake_clean_target.cmake
	cd /home/sci/weiliu/projects/groupising/gco && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graphcuts.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
gco/CMakeFiles/graphcuts.dir/build: gco/libgraphcuts.a
.PHONY : gco/CMakeFiles/graphcuts.dir/build

gco/CMakeFiles/graphcuts.dir/requires: gco/CMakeFiles/graphcuts.dir/GCoptimization.cpp.o.requires
gco/CMakeFiles/graphcuts.dir/requires: gco/CMakeFiles/graphcuts.dir/graph.cpp.o.requires
gco/CMakeFiles/graphcuts.dir/requires: gco/CMakeFiles/graphcuts.dir/LinkedBlockList.cpp.o.requires
gco/CMakeFiles/graphcuts.dir/requires: gco/CMakeFiles/graphcuts.dir/maxflow.cpp.o.requires
.PHONY : gco/CMakeFiles/graphcuts.dir/requires

gco/CMakeFiles/graphcuts.dir/clean:
	cd /home/sci/weiliu/projects/groupising/gco && $(CMAKE_COMMAND) -P CMakeFiles/graphcuts.dir/cmake_clean.cmake
.PHONY : gco/CMakeFiles/graphcuts.dir/clean

gco/CMakeFiles/graphcuts.dir/depend:
	cd /home/sci/weiliu/projects/groupising && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sci/weiliu/projects/groupising /home/sci/weiliu/projects/groupising/gco /home/sci/weiliu/projects/groupising /home/sci/weiliu/projects/groupising/gco /home/sci/weiliu/projects/groupising/gco/CMakeFiles/graphcuts.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : gco/CMakeFiles/graphcuts.dir/depend

