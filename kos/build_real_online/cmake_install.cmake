# Install script for directory: /home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/../install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/opt/KasperskyOS-Community-Edition-1.2.0.45/toolchain/bin/aarch64-kos-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/Initialization.idl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/Initialization.idl.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/AutopilotConnectorInterface.idl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/AutopilotConnectorInterface.idl.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/CredentialManagerInterface.idl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/CredentialManagerInterface.idl.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/NavigationSystemInterface.idl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/NavigationSystemInterface.idl.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/PeripheryControllerInterface.idl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/PeripheryControllerInterface.idl.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/ServerConnectorInterface.idl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/ServerConnectorInterface.idl.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/AutopilotConnector.edl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/AutopilotConnector.edl.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/CredentialManager.edl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/CredentialManager.edl.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/NavigationSystem.edl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/NavigationSystem.edl.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/PeripheryController.edl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/PeripheryController.edl.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/ServerConnector.edl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/ServerConnector.edl.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "nk_headers" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/drone_controller" TYPE FILE FILES
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/FlightController.edl"
    "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/_headers_/DroneController/../drone_controller/FlightController.edl.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/autopilot_connector/cmake_install.cmake")
  include("/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/credential_manager/cmake_install.cmake")
  include("/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/flight_controller/cmake_install.cmake")
  include("/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/navigation_system/cmake_install.cmake")
  include("/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/periphery_controller/cmake_install.cmake")
  include("/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/server_connector/cmake_install.cmake")
  include("/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/einit/real_online/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/maximkrasavtsev/cyberimmune-systems-autonomous-delivery-drone-with-kos-fork/kos/build_real_online/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
