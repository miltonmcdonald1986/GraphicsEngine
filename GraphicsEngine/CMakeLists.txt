################################################################################
# Specify the locations of all source files for this project                   #
################################################################################

file(GLOB ENGINE_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/glad/glad.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/KHR/khrplatform.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert"
	"${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag"
	"${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.geom"
)

################################################################################
# Create filters for each directory                                            #
################################################################################

foreach(FILE IN LISTS ENGINE_SRC)
    get_filename_component(PATH "${FILE}" PATH)
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${PATH}")
    string(REPLACE "/" "\\" FILTER "${REL_PATH}")
    source_group("${FILTER}" FILES "${FILE}")
endforeach()

################################################################################
# Define GRAPHICSENGINE_EXPORTS for Windows dll creation.                      #
################################################################################

add_library(GraphicsEngine SHARED ${ENGINE_SRC})
target_compile_definitions(GraphicsEngine PRIVATE GRAPHICSENGINE_EXPORTS)

################################################################################
# Precompiled header information                                               #
################################################################################

target_precompile_headers(GraphicsEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h)
file(GLOB_RECURSE PCH_FILES
    "${CMAKE_BINARY_DIR}/cmake_pch.*"
	"${CMAKE_CURRENT_SOURCE_DIR}/pch.*"
)
source_group("precompiled" FILES ${PCH_FILES})

################################################################################
# Additional include directories                                               #
################################################################################

target_include_directories(GraphicsEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_include_directories(GraphicsEngine PRIVATE ${Stb_INCLUDE_DIR})

################################################################################
# Libraries                                                                    #
################################################################################

target_link_libraries(GraphicsEngine PRIVATE spdlog::spdlog)
target_link_libraries(GraphicsEngine PRIVATE glm::glm)

################################################################################
# Use shared output directory for this project                                 #
################################################################################

set_target_properties(GraphicsEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SHARED_OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${SHARED_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${SHARED_OUTPUT_DIR}
)

################################################################################
# Copy the shaders to the output directory so they can be found                #
################################################################################

set(SHADER_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set(SHADER_OUT_DIR "${SHARED_OUTPUT_DIR}/$<CONFIG>/shaders")
else()
	set(SHADER_OUT_DIR "${SHARED_OUTPUT_DIR}/shaders")
endif()

add_custom_command(
	TARGET GraphicsEngine
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${SHADER_SOURCE_DIR}
		${SHADER_OUT_DIR}
)
