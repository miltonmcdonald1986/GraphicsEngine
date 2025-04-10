################################################################################
# GraphicsEngine source files and filters                                      #
################################################################################

file(GLOB ENGINE_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# Create filters for include, src, etc.
foreach(FILE IN LISTS ENGINE_SRC)
    get_filename_component(PATH "${FILE}" PATH)
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${PATH}")
    string(REPLACE "/" "\\" FILTER "${REL_PATH}")
    source_group("${FILTER}" FILES "${FILE}")
endforeach()

################################################################################
# GraphicsEngine library settings                                              #
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

# Create filter for precompiled header files.
source_group("precompiled" FILES ${PCH_FILES})

################################################################################
# Additional include directories                                               #
################################################################################

target_include_directories(GraphicsEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${stb_SOURCE_DIR}
	${glm_SOURCE_DIR}
)

################################################################################
# spdlog library                                                               #
################################################################################

target_link_libraries(GraphicsEngine PRIVATE spdlog)
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	target_compile_options(spdlog PRIVATE -fPIC)
endif()
target_compile_definitions(GraphicsEngine
    PRIVATE SPDLOG_USE_STD_FORMAT
)

################################################################################
# glad library                                                                 #
################################################################################

add_library(glad ../lib/glad/include/glad/glad.h ../lib/glad/src/glad.c)
target_include_directories(glad PUBLIC ../lib/glad/include)
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	target_compile_options(glad PRIVATE -fPIC)
endif()
target_link_libraries(GraphicsEngine PRIVATE glad)
