cmake_minimum_required(VERSION 3.10)
project(GraphicsEngine)

option(RUN_POWERSHELL_SCRIPTS "Run PowerShell scripts during configuration" OFF)
option(RUN_BASH_SCRIPTS "Run Bash scripts during configuration" OFF)

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

# Get spdlog

if (RUN_POWERSHELL_SCRIPTS)
	execute_process(
		COMMAND powershell -File fetch_spdlog.ps1
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE script_result
	)

	if(NOT script_result EQUAL 0)
		message(FATAL_ERROR "PowerShell script failed with result code: ${script_result}")
	endif()

	# Get GLFW

	execute_process(
		COMMAND powershell -File fetch_glfw.ps1
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE script_result
	)

	if(NOT script_result EQUAL 0)
		message(FATAL_ERROR "PowerShell script failed with result code: ${script_result}")
	endif()

	# Get imgui

	execute_process(
		COMMAND powershell -File fetch_imgui.ps1
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE script_result
	)

	if(NOT script_result EQUAL 0)
		message(FATAL_ERROR "PowerShell script failed with result code: ${script_result}")
	endif()
	
	# Get stb

	execute_process(
		COMMAND powershell -File fetch_stb.ps1
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE script_result
	)

	if(NOT script_result EQUAL 0)
		message(FATAL_ERROR "PowerShell script failed with result code: ${script_result}")
	endif()
elseif(RUN_BASH_SCRIPTS) 	
    execute_process(
	COMMAND bash fetch_spdlog.sh
	    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	    RESULT_VARIABLE script_result
	)

	if(NOT script_result EQUAL 0)
		message(FATAL_ERROR "Bash script failed with result code: ${script_result}")
	endif()
	
    execute_process(
	COMMAND bash fetch_glfw.sh
	    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	    RESULT_VARIABLE script_result
	)

	if(NOT script_result EQUAL 0)
		message(FATAL_ERROR "Bash script failed with result code: ${script_result}")
	endif()
	
    execute_process(
	COMMAND bash fetch_imgui.sh
	    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	    RESULT_VARIABLE script_result
	)

	if(NOT script_result EQUAL 0)
		message(FATAL_ERROR "Bash script failed with result code: ${script_result}")
	endif()
endif()
