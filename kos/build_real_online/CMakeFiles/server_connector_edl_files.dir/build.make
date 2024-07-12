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
include CMakeFiles/server_connector_edl_files.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server_connector_edl_files.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server_connector_edl_files.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server_connector_edl_files.dir/flags.make

_headers_/drone_controller/ServerConnector.edl.h:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating _headers_/drone_controller/ServerConnector.edl.h"
	/opt/KasperskyOS-Community-Edition-1.2.0.45/toolchain/bin/cmake -E copy_if_different /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/ServerConnector.edl.h /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/ServerConnector.edl.h

server_connector_edl_files: CMakeFiles/server_connector_edl_files.dir/build.make
.PHONY : server_connector_edl_files

# Rule to build all files generated by this target.
CMakeFiles/server_connector_edl_files.dir/build: server_connector_edl_files
.PHONY : CMakeFiles/server_connector_edl_files.dir/build

CMakeFiles/server_connector_edl_files.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server_connector_edl_files.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server_connector_edl_files.dir/clean

CMakeFiles/server_connector_edl_files.dir/depend: _headers_/drone_controller/ServerConnector.edl.h
	cd /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/CMakeFiles/server_connector_edl_files.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server_connector_edl_files.dir/depend
