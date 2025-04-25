find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Stb REQUIRED)

file(GLOB ENGINE_INTERFACES "${CMAKE_CURRENT_SOURCE_DIR}/include/GraphicsEngine/*.h")
file(GLOB ENGINE_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB ENGINE_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

file(GLOB ENGINE_SRC 
	${ENGINE_INTERFACES}
	${ENGINE_HEADER_FILES}
	${ENGINE_SOURCE_FILES}
)
source_group("Interfaces" FILES ${ENGINE_INTERFACES})
source_group("Header Files" FILES ${ENGINE_HEADER_FILES})
source_group("Source Files" FILES ${ENGINE_SOURCE_FILES})

add_library(GraphicsEngine SHARED ${ENGINE_SRC})
target_compile_definitions(GraphicsEngine PRIVATE GRAPHICSENGINE_EXPORTS)

target_include_directories(GraphicsEngine 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/GraphicsEngine
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
	PRIVATE ${Stb_INCLUDE_DIR}
)

target_precompile_headers(GraphicsEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")

target_link_libraries(GraphicsEngine PRIVATE glm::glm)
target_link_libraries(GraphicsEngine PRIVATE spdlog::spdlog_header_only)
