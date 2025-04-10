cmake_minimum_required(VERSION 3.11)
project(GraphicsEngine)

################################################################################
# Load CMake modules                                                           #
################################################################################

include(FetchContent)

################################################################################
# C++ Standard                                                                 #
################################################################################

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

################################################################################
# Set warning levels                                                           #
################################################################################

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif()

################################################################################
# Visual Studio Properties                                                     #
################################################################################

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

################################################################################
# Dependencies                                                                 #
################################################################################

# GLFW
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# spdlog
FetchContent_Declare(
	spdlog
	GIT_REPOSITORY https://github.com/gabime/spdlog.git
	GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(spdlog)

# imgui
FetchContent_Declare(
	imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG v1.91.9b-docking
)
FetchContent_MakeAvailable(imgui)

# stb
FetchContent_Declare(
	stb
	GIT_REPOSITORY https://github.com/nothings/stb.git
	GIT_TAG master
)
FetchContent_MakeAvailable(stb)

# glm
FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

################################################################################
# Add a subdirectory for each project in this repository.                      #
################################################################################

add_subdirectory(GraphicsEngine)
add_subdirectory(Sandbox)
