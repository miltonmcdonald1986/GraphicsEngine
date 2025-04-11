cmake_minimum_required(VERSION 3.11)
project(GraphicsEngine)

################################################################################
# Set the C++ standard										                   #
################################################################################

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

################################################################################
# Set warning levels  										                   #
################################################################################

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif()

################################################################################
# For Visual Studio, Sandbox is our startup project                            #
################################################################################

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

################################################################################
# Set the vcpkg toolchain file location                                        #
################################################################################

if(NOT DEFINED ENV{VCPKG_ROOT})
	message(FATAL_ERROR "The environment variable VCPKG_ROOT is not set!")
else()
	set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif()

################################################################################
# Specify our dependencies                                                     #
################################################################################

find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(imgui CONFIG REQUIRED)

################################################################################
# Create the projects                                                          #
################################################################################

add_subdirectory(GraphicsEngine)
add_subdirectory(Sandbox)
