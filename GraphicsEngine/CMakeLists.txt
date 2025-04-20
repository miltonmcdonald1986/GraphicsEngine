find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Stb REQUIRED)

file(GLOB ENGINE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(GraphicsEngine SHARED ${ENGINE_SRC})
target_compile_definitions(GraphicsEngine PRIVATE GRAPHICSENGINE_EXPORTS)

target_include_directories(GraphicsEngine 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/GraphicsEngine
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
	PRIVATE ${Stb_INCLUDE_DIR}
)

target_link_libraries(GraphicsEngine PRIVATE glm::glm)
target_link_libraries(GraphicsEngine PRIVATE spdlog::spdlog_header_only)
