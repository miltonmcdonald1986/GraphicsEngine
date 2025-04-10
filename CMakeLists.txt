cmake_minimum_required(VERSION 3.10)
project(GraphicsEngine)

option(DOWNLOAD_DEPENDENCIES "Download and install all dependencies to the lib folder." OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message("THIS IS LINUX")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
endif()

message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")

# Add subdirectories for the engine and sandbox
# add_subdirectory(lib/spdlog)
add_subdirectory(GraphicsEngine)
add_subdirectory(Sandbox)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

# Fetch GLFW
	
include(FetchContent)
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# Fetch spdlog
	
include(FetchContent)
FetchContent_Declare(
	spdlog
	GIT_REPOSITORY https://github.com/gabime/spdlog.git
	GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(spdlog)

# Get spdlog

if (DOWNLOAD_DEPENDENCIES)
		
	# Fetch imgui
	
	if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
		execute_process(
			COMMAND bash fetch_imgui.sh
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE script_result
		)
	elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
		execute_process(
			COMMAND powershell -File fetch_imgui.ps1
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE script_result
		)
	endif()

	if(NOT script_result EQUAL 0)
		message(FATAL_ERROR "Failed to fetch imgui: ${script_result}")
	endif()

	# Fetch stb
	
	if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
		execute_process(
			COMMAND bash fetch_stb.sh
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE script_result
		)
	elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
		execute_process(
			COMMAND powershell -File fetch_stb.ps1
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE script_result
		)
	endif()

	if(NOT script_result EQUAL 0)
		message(FATAL_ERROR "Failed to fetch stb: ${script_result}")
	endif()	
	
	# Fetch glm
	
	if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
		execute_process(
			COMMAND bash fetch_glm.sh
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE script_result
		)
	elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
		execute_process(
			COMMAND powershell -File fetch_glm.ps1
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE script_result
		)
	endif()

	if(NOT script_result EQUAL 0)
		message(FATAL_ERROR "Failed to fetch glm: ${script_result}")
	endif()	

endif()
