# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /opt/KasperskyOS-Community-Edition-1.2.0.45/toolchain/bin/cmake

# The command to remove a file.
RM = /opt/KasperskyOS-Community-Edition-1.2.0.45/toolchain/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online

# Include any dependencies generated for this target.
include CMakeFiles/initialization_idl_files.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/initialization_idl_files.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/initialization_idl_files.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/initialization_idl_files.dir/flags.make

_headers_/drone_controller/Initialization.idl.h:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating _headers_/drone_controller/Initialization.idl.h"
	/opt/KasperskyOS-Community-Edition-1.2.0.45/toolchain/bin/cmake -E copy_if_different /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/Initialization.idl.h /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/Initialization.idl.h

initialization_idl_files: CMakeFiles/initialization_idl_files.dir/build.make
.PHONY : initialization_idl_files

# Rule to build all files generated by this target.
CMakeFiles/initialization_idl_files.dir/build: initialization_idl_files
.PHONY : CMakeFiles/initialization_idl_files.dir/build

CMakeFiles/initialization_idl_files.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/initialization_idl_files.dir/cmake_clean.cmake
.PHONY : CMakeFiles/initialization_idl_files.dir/clean

CMakeFiles/initialization_idl_files.dir/depend: _headers_/drone_controller/Initialization.idl.h
	cd /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/CMakeFiles/initialization_idl_files.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/initialization_idl_files.dir/depend
