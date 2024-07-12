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

# Utility rule file for flight_controller_edl_files_gen_drone_controller.FlightController.edl.

# Include any custom commands dependencies for this target.
include CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl.dir/progress.make

CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl: FlightController.edl.h

FlightController.edl.h:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating FlightController.edl.h"
	/opt/KasperskyOS-Community-Edition-1.2.0.45/toolchain/bin/nk-gen-c -I /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_ -I /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/.. -I /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/../install/include -I /opt/KasperskyOS-Community-Edition-1.2.0.45/sysroot-aarch64-kos/include -I /opt/KasperskyOS-Community-Edition-1.2.0.45/toolchain/aarch64-kos/include -I /usr/local/include -I /usr/include -I //include -I /opt/KasperskyOS-Community-Edition-1.2.0.45/toolchain/include -I /usr/X11R6/include -I /usr/pkg/include -I /opt/include -I /opt/KasperskyOS-Local-Edition/sysroot-aarch64-kos/include -P /opt/KasperskyOS-Local-Edition/sysroot-aarch64-kos/include/system.platform -I /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/FlightController.edl

flight_controller_edl_files_gen_drone_controller.FlightController.edl: CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl
flight_controller_edl_files_gen_drone_controller.FlightController.edl: FlightController.edl.h
flight_controller_edl_files_gen_drone_controller.FlightController.edl: CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl.dir/build.make
.PHONY : flight_controller_edl_files_gen_drone_controller.FlightController.edl

# Rule to build all files generated by this target.
CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl.dir/build: flight_controller_edl_files_gen_drone_controller.FlightController.edl
.PHONY : CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl.dir/build

CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl.dir/clean

CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl.dir/depend:
	cd /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/flight_controller_edl_files_gen_drone_controller.FlightController.edl.dir/depend
