file(GLOB_RECURSE SANDBOX_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(Sandbox ${SANDBOX_SRC})

target_include_directories(Sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/App
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Widget
)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	target_link_options(Sandbox PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
endif()

target_link_libraries(Sandbox PRIVATE GraphicsEngine)

# Loop through files and assign filters dynamically
foreach(FILE IN LISTS SANDBOX_SRC)
    get_filename_component(PATH "${FILE}" PATH)
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src" "${PATH}")
    string(REPLACE "/" "\\" FILTER "${REL_PATH}")
    source_group("${FILTER}" FILES "${FILE}")
endforeach()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	target_link_libraries(your_target PRIVATE glfw)
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	# Specify GLFW's include path and library path manually
	target_include_directories(Sandbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/GLFW/include)
	target_link_libraries(Sandbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/GLFW/lib-vc2022/glfw3dll.lib)
endif()

# Add the Dear ImGui source files

set(IMGUI_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/imgui/imgui.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../lib/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/imgui/backends/imgui_impl_glfw.cpp
)

# Include the ImGui headers
target_include_directories(Sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/imgui/backends
)

# Add the ImGui sources to the Sandbox target
target_sources(Sandbox PRIVATE ${IMGUI_SOURCES})
source_group("imgui" FILES ${IMGUI_SOURCES})

#post build events to copy dlls

add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:GraphicsEngine>  # Path to the DLL
        $<TARGET_FILE_DIR:Sandbox>    # Path to the executable directory
)

add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/../lib/GLFW/lib-vc2022/glfw3.dll"  # Path to the DLL
        $<TARGET_FILE_DIR:Sandbox>    # Path to the executable directory
)

# glm

target_include_directories(GraphicsEngine PUBLIC ../lib/glm)