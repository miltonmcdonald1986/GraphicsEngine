cmake_minimum_required(VERSION 3.10)
project(GraphicsEngine)
include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	# message("THIS IS LINUX")
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
# endif()

# message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
# message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

# Fetch GLFW
	
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# Fetch spdlog
	
FetchContent_Declare(
	spdlog
	GIT_REPOSITORY https://github.com/gabime/spdlog.git
	GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(spdlog)

# Fetch imgui
	
FetchContent_Declare(
	imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG v1.91.9b-docking
)
FetchContent_MakeAvailable(imgui)

# Fetch stb

FetchContent_Declare(
	stb
	GIT_REPOSITORY https://github.com/nothings/stb.git
	GIT_TAG master
)
FetchContent_MakeAvailable(stb)

# Fetch glm

FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

add_subdirectory(GraphicsEngine)
add_subdirectory(Sandbox)
