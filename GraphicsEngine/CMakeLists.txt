################################################################################
# Specify the locations of all source files for this project                   #
################################################################################

file(GLOB ENGINE_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/glad/glad.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/KHR/khrplatform.h"
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
