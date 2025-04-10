################################################################################
# Sandbox source files and filters                                             #
################################################################################

file(GLOB_RECURSE SANDBOX_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# Create filters for App, Widget, etc.
foreach(FILE IN LISTS SANDBOX_SRC)
    get_filename_component(PATH "${FILE}" PATH)
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src" "${PATH}")
    string(REPLACE "/" "\\" FILTER "${REL_PATH}")
    source_group("${FILTER}" FILES "${FILE}")
endforeach()

################################################################################
# Sandbox application settings                                                 #
################################################################################

add_executable(Sandbox ${SANDBOX_SRC})

# Windows: Set as a Windows application with entry point 'main'.
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	target_link_options(Sandbox PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
endif()

################################################################################
# Additional include directories                                               #
################################################################################

target_include_directories(Sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/App
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Widget
	${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

################################################################################
# Dear ImGui library                                                           #
################################################################################

add_library(imgui STATIC
	${imgui_SOURCE_DIR}/imgui.h
    ${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
)

target_include_directories(imgui PRIVATE
    ${glfw_SOURCE_DIR}/include
	${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(Sandbox PRIVATE imgui)

################################################################################
# Additional libraries                                                         #
################################################################################

target_link_libraries(Sandbox PRIVATE GraphicsEngine)
target_link_libraries(Sandbox PRIVATE glfw)

################################################################################
# Post-build events in Windows                                                 #
################################################################################

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

	# Copy the GraphicsEngine dll to the Sandbox output directory.
	add_custom_command(TARGET Sandbox POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:GraphicsEngine> 	# Path to the DLL
			$<TARGET_FILE_DIR:Sandbox>   	# Path to the executable directory
	)
	
endif()
