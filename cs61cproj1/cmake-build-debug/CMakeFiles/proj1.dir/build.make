# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/familyyepez/Desktop/cs61cproj1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/familyyepez/Desktop/cs61cproj1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/proj1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/proj1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/proj1.dir/flags.make

CMakeFiles/proj1.dir/part1.c.o: CMakeFiles/proj1.dir/flags.make
CMakeFiles/proj1.dir/part1.c.o: ../part1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/familyyepez/Desktop/cs61cproj1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/proj1.dir/part1.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/proj1.dir/part1.c.o   -c /Users/familyyepez/Desktop/cs61cproj1/part1.c

CMakeFiles/proj1.dir/part1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/proj1.dir/part1.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/familyyepez/Desktop/cs61cproj1/part1.c > CMakeFiles/proj1.dir/part1.c.i

CMakeFiles/proj1.dir/part1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/proj1.dir/part1.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/familyyepez/Desktop/cs61cproj1/part1.c -o CMakeFiles/proj1.dir/part1.c.s

CMakeFiles/proj1.dir/part2.c.o: CMakeFiles/proj1.dir/flags.make
CMakeFiles/proj1.dir/part2.c.o: ../part2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/familyyepez/Desktop/cs61cproj1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/proj1.dir/part2.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/proj1.dir/part2.c.o   -c /Users/familyyepez/Desktop/cs61cproj1/part2.c

CMakeFiles/proj1.dir/part2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/proj1.dir/part2.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/familyyepez/Desktop/cs61cproj1/part2.c > CMakeFiles/proj1.dir/part2.c.i

CMakeFiles/proj1.dir/part2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/proj1.dir/part2.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/familyyepez/Desktop/cs61cproj1/part2.c -o CMakeFiles/proj1.dir/part2.c.s

CMakeFiles/proj1.dir/riscv.c.o: CMakeFiles/proj1.dir/flags.make
CMakeFiles/proj1.dir/riscv.c.o: ../riscv.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/familyyepez/Desktop/cs61cproj1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/proj1.dir/riscv.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/proj1.dir/riscv.c.o   -c /Users/familyyepez/Desktop/cs61cproj1/riscv.c

CMakeFiles/proj1.dir/riscv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/proj1.dir/riscv.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/familyyepez/Desktop/cs61cproj1/riscv.c > CMakeFiles/proj1.dir/riscv.c.i

CMakeFiles/proj1.dir/riscv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/proj1.dir/riscv.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/familyyepez/Desktop/cs61cproj1/riscv.c -o CMakeFiles/proj1.dir/riscv.c.s

CMakeFiles/proj1.dir/utils.c.o: CMakeFiles/proj1.dir/flags.make
CMakeFiles/proj1.dir/utils.c.o: ../utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/familyyepez/Desktop/cs61cproj1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/proj1.dir/utils.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/proj1.dir/utils.c.o   -c /Users/familyyepez/Desktop/cs61cproj1/utils.c

CMakeFiles/proj1.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/proj1.dir/utils.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/familyyepez/Desktop/cs61cproj1/utils.c > CMakeFiles/proj1.dir/utils.c.i

CMakeFiles/proj1.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/proj1.dir/utils.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/familyyepez/Desktop/cs61cproj1/utils.c -o CMakeFiles/proj1.dir/utils.c.s

# Object files for target proj1
proj1_OBJECTS = \
"CMakeFiles/proj1.dir/part1.c.o" \
"CMakeFiles/proj1.dir/part2.c.o" \
"CMakeFiles/proj1.dir/riscv.c.o" \
"CMakeFiles/proj1.dir/utils.c.o"

# External object files for target proj1
proj1_EXTERNAL_OBJECTS =

proj1: CMakeFiles/proj1.dir/part1.c.o
proj1: CMakeFiles/proj1.dir/part2.c.o
proj1: CMakeFiles/proj1.dir/riscv.c.o
proj1: CMakeFiles/proj1.dir/utils.c.o
proj1: CMakeFiles/proj1.dir/build.make
proj1: CMakeFiles/proj1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/familyyepez/Desktop/cs61cproj1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable proj1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proj1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/proj1.dir/build: proj1

.PHONY : CMakeFiles/proj1.dir/build

CMakeFiles/proj1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/proj1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/proj1.dir/clean

CMakeFiles/proj1.dir/depend:
	cd /Users/familyyepez/Desktop/cs61cproj1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/familyyepez/Desktop/cs61cproj1 /Users/familyyepez/Desktop/cs61cproj1 /Users/familyyepez/Desktop/cs61cproj1/cmake-build-debug /Users/familyyepez/Desktop/cs61cproj1/cmake-build-debug /Users/familyyepez/Desktop/cs61cproj1/cmake-build-debug/CMakeFiles/proj1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/proj1.dir/depend

