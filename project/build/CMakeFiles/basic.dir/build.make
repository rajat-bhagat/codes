# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/einfochips/lib/cmake/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/einfochips/lib/cmake/project/build

# Include any dependencies generated for this target.
include CMakeFiles/basic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/basic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/basic.dir/flags.make

CMakeFiles/basic.dir/src/add/add.c.o: CMakeFiles/basic.dir/flags.make
CMakeFiles/basic.dir/src/add/add.c.o: ../src/add/add.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/einfochips/lib/cmake/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/basic.dir/src/add/add.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/basic.dir/src/add/add.c.o   -c /home/einfochips/lib/cmake/project/src/add/add.c

CMakeFiles/basic.dir/src/add/add.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/basic.dir/src/add/add.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/einfochips/lib/cmake/project/src/add/add.c > CMakeFiles/basic.dir/src/add/add.c.i

CMakeFiles/basic.dir/src/add/add.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/basic.dir/src/add/add.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/einfochips/lib/cmake/project/src/add/add.c -o CMakeFiles/basic.dir/src/add/add.c.s

CMakeFiles/basic.dir/src/add/add.c.o.requires:

.PHONY : CMakeFiles/basic.dir/src/add/add.c.o.requires

CMakeFiles/basic.dir/src/add/add.c.o.provides: CMakeFiles/basic.dir/src/add/add.c.o.requires
	$(MAKE) -f CMakeFiles/basic.dir/build.make CMakeFiles/basic.dir/src/add/add.c.o.provides.build
.PHONY : CMakeFiles/basic.dir/src/add/add.c.o.provides

CMakeFiles/basic.dir/src/add/add.c.o.provides.build: CMakeFiles/basic.dir/src/add/add.c.o


CMakeFiles/basic.dir/src/sub/sub.c.o: CMakeFiles/basic.dir/flags.make
CMakeFiles/basic.dir/src/sub/sub.c.o: ../src/sub/sub.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/einfochips/lib/cmake/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/basic.dir/src/sub/sub.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/basic.dir/src/sub/sub.c.o   -c /home/einfochips/lib/cmake/project/src/sub/sub.c

CMakeFiles/basic.dir/src/sub/sub.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/basic.dir/src/sub/sub.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/einfochips/lib/cmake/project/src/sub/sub.c > CMakeFiles/basic.dir/src/sub/sub.c.i

CMakeFiles/basic.dir/src/sub/sub.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/basic.dir/src/sub/sub.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/einfochips/lib/cmake/project/src/sub/sub.c -o CMakeFiles/basic.dir/src/sub/sub.c.s

CMakeFiles/basic.dir/src/sub/sub.c.o.requires:

.PHONY : CMakeFiles/basic.dir/src/sub/sub.c.o.requires

CMakeFiles/basic.dir/src/sub/sub.c.o.provides: CMakeFiles/basic.dir/src/sub/sub.c.o.requires
	$(MAKE) -f CMakeFiles/basic.dir/build.make CMakeFiles/basic.dir/src/sub/sub.c.o.provides.build
.PHONY : CMakeFiles/basic.dir/src/sub/sub.c.o.provides

CMakeFiles/basic.dir/src/sub/sub.c.o.provides.build: CMakeFiles/basic.dir/src/sub/sub.c.o


# Object files for target basic
basic_OBJECTS = \
"CMakeFiles/basic.dir/src/add/add.c.o" \
"CMakeFiles/basic.dir/src/sub/sub.c.o"

# External object files for target basic
basic_EXTERNAL_OBJECTS =

libbasic.so: CMakeFiles/basic.dir/src/add/add.c.o
libbasic.so: CMakeFiles/basic.dir/src/sub/sub.c.o
libbasic.so: CMakeFiles/basic.dir/build.make
libbasic.so: CMakeFiles/basic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/einfochips/lib/cmake/project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C shared library libbasic.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/basic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/basic.dir/build: libbasic.so

.PHONY : CMakeFiles/basic.dir/build

CMakeFiles/basic.dir/requires: CMakeFiles/basic.dir/src/add/add.c.o.requires
CMakeFiles/basic.dir/requires: CMakeFiles/basic.dir/src/sub/sub.c.o.requires

.PHONY : CMakeFiles/basic.dir/requires

CMakeFiles/basic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/basic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/basic.dir/clean

CMakeFiles/basic.dir/depend:
	cd /home/einfochips/lib/cmake/project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/einfochips/lib/cmake/project /home/einfochips/lib/cmake/project /home/einfochips/lib/cmake/project/build /home/einfochips/lib/cmake/project/build /home/einfochips/lib/cmake/project/build/CMakeFiles/basic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/basic.dir/depend

