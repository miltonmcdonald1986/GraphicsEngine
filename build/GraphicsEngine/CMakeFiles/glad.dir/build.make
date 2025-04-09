# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_SOURCE_DIR = /home/milton/source/repos/GraphicsEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/milton/source/repos/GraphicsEngine/build

# Include any dependencies generated for this target.
include GraphicsEngine/CMakeFiles/glad.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include GraphicsEngine/CMakeFiles/glad.dir/compiler_depend.make

# Include the progress variables for this target.
include GraphicsEngine/CMakeFiles/glad.dir/progress.make

# Include the compile flags for this target's objects.
include GraphicsEngine/CMakeFiles/glad.dir/flags.make

GraphicsEngine/CMakeFiles/glad.dir/codegen:
.PHONY : GraphicsEngine/CMakeFiles/glad.dir/codegen

GraphicsEngine/CMakeFiles/glad.dir/__/lib/glad/src/glad.c.o: GraphicsEngine/CMakeFiles/glad.dir/flags.make
GraphicsEngine/CMakeFiles/glad.dir/__/lib/glad/src/glad.c.o: /home/milton/source/repos/GraphicsEngine/lib/glad/src/glad.c
GraphicsEngine/CMakeFiles/glad.dir/__/lib/glad/src/glad.c.o: GraphicsEngine/CMakeFiles/glad.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/milton/source/repos/GraphicsEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object GraphicsEngine/CMakeFiles/glad.dir/__/lib/glad/src/glad.c.o"
	cd /home/milton/source/repos/GraphicsEngine/build/GraphicsEngine && /usr/bin/gcc-13 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT GraphicsEngine/CMakeFiles/glad.dir/__/lib/glad/src/glad.c.o -MF CMakeFiles/glad.dir/__/lib/glad/src/glad.c.o.d -o CMakeFiles/glad.dir/__/lib/glad/src/glad.c.o -c /home/milton/source/repos/GraphicsEngine/lib/glad/src/glad.c

GraphicsEngine/CMakeFiles/glad.dir/__/lib/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/glad.dir/__/lib/glad/src/glad.c.i"
	cd /home/milton/source/repos/GraphicsEngine/build/GraphicsEngine && /usr/bin/gcc-13 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/milton/source/repos/GraphicsEngine/lib/glad/src/glad.c > CMakeFiles/glad.dir/__/lib/glad/src/glad.c.i

GraphicsEngine/CMakeFiles/glad.dir/__/lib/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/glad.dir/__/lib/glad/src/glad.c.s"
	cd /home/milton/source/repos/GraphicsEngine/build/GraphicsEngine && /usr/bin/gcc-13 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/milton/source/repos/GraphicsEngine/lib/glad/src/glad.c -o CMakeFiles/glad.dir/__/lib/glad/src/glad.c.s

# Object files for target glad
glad_OBJECTS = \
"CMakeFiles/glad.dir/__/lib/glad/src/glad.c.o"

# External object files for target glad
glad_EXTERNAL_OBJECTS =

GraphicsEngine/libglad.a: GraphicsEngine/CMakeFiles/glad.dir/__/lib/glad/src/glad.c.o
GraphicsEngine/libglad.a: GraphicsEngine/CMakeFiles/glad.dir/build.make
GraphicsEngine/libglad.a: GraphicsEngine/CMakeFiles/glad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/milton/source/repos/GraphicsEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libglad.a"
	cd /home/milton/source/repos/GraphicsEngine/build/GraphicsEngine && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean_target.cmake
	cd /home/milton/source/repos/GraphicsEngine/build/GraphicsEngine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
GraphicsEngine/CMakeFiles/glad.dir/build: GraphicsEngine/libglad.a
.PHONY : GraphicsEngine/CMakeFiles/glad.dir/build

GraphicsEngine/CMakeFiles/glad.dir/clean:
	cd /home/milton/source/repos/GraphicsEngine/build/GraphicsEngine && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean.cmake
.PHONY : GraphicsEngine/CMakeFiles/glad.dir/clean

GraphicsEngine/CMakeFiles/glad.dir/depend:
	cd /home/milton/source/repos/GraphicsEngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/milton/source/repos/GraphicsEngine /home/milton/source/repos/GraphicsEngine/GraphicsEngine /home/milton/source/repos/GraphicsEngine/build /home/milton/source/repos/GraphicsEngine/build/GraphicsEngine /home/milton/source/repos/GraphicsEngine/build/GraphicsEngine/CMakeFiles/glad.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : GraphicsEngine/CMakeFiles/glad.dir/depend

