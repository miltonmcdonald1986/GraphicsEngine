file(GLOB ENGINE_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# Define the library
add_library(GraphicsEngine SHARED ${ENGINE_SRC})

# Include directories for public headers
target_include_directories(GraphicsEngine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(GraphicsEngine PRIVATE GRAPHICSENGINE_EXPORTS)

# Loop through files and assign filters dynamically
foreach(FILE IN LISTS ENGINE_SRC)
    get_filename_component(PATH "${FILE}" PATH)
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${PATH}")
    string(REPLACE "/" "\\" FILTER "${REL_PATH}")
    source_group("${FILTER}" FILES "${FILE}")
endforeach()

target_precompile_headers(GraphicsEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h)

file(GLOB_RECURSE PCH_FILES
    "${CMAKE_BINARY_DIR}/cmake_pch.*"
	"${CMAKE_CURRENT_SOURCE_DIR}/pch.*"
)

# Assign an empty filter for all matched files
source_group("precompiled" FILES ${PCH_FILES})

# spdlog
target_include_directories(GraphicsEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/spdlog/include)
#target_link_libraries(GraphicsEngine PUBLIC spdlog::spdlog)
target_compile_definitions(GraphicsEngine
    PRIVATE SPDLOG_USE_STD_FORMAT
)

# glad

add_library(glad ../lib/glad/src/glad.c)
target_include_directories(glad PUBLIC ../lib/glad/include)
target_link_libraries(GraphicsEngine PRIVATE glad)

# stb

target_include_directories(GraphicsEngine PUBLIC ../lib/stb)
