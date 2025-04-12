cmake_minimum_required(VERSION 3.10)
project(GraphicsEngine)

################################################################################
# CMAKE options       										                   #
################################################################################

#option(BUILD_SANDBOX "Build Sandbox" ON)

################################################################################
# Set shared output directories for all projects                               #
################################################################################

#set(SHARED_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SHARED_OUTPUT_DIR})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SHARED_OUTPUT_DIR})
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SHARED_OUTPUT_DIR})

################################################################################
# Set the C++ standard										                   #
################################################################################

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

################################################################################
# Set warning levels  										                   #
################################################################################

#if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#    add_compile_options(-Wall -Wextra -Wpedantic)
#elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#    add_compile_options(/W4)
#endif()

################################################################################
# For Visual Studio, Sandbox is our startup project                            #
################################################################################

#if (BUILD_SANDBOX)
#	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
#endif()

################################################################################
# Set the vcpkg toolchain file location                                        #
################################################################################

#if(NOT DEFINED ENV{VCPKG_ROOT})
#	message(FATAL_ERROR "The environment variable VCPKG_ROOT is not set!")
#else()
#	message("My env var is $ENV{VCPKG_ROOT}")
#	set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
#endif()
#if (UNIX)
#	set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-linux/include" CACHE STRING "Path to vcpkg dependencies")
#endif()

################################################################################
# Specify our dependencies                                                     #
################################################################################

find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Stb REQUIRED)
#if (BUILD_SANDBOX)
#	find_package(imgui CONFIG REQUIRED)
#	find_package(glfw3 CONFIG REQUIRED)
#endif()

################################################################################
# Create the projects                                                          #
################################################################################

add_subdirectory(GraphicsEngine)
#if(BUILD_SANDBOX)
#    add_subdirectory(Sandbox)
#endif()
