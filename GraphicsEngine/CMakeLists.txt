find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Stb REQUIRED)

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

add_library(GraphicsEngine SHARED ${ENGINE_SRC})
target_compile_definitions(GraphicsEngine PRIVATE GRAPHICSENGINE_EXPORTS)

target_include_directories(GraphicsEngine 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
	PRIVATE ${Stb_INCLUDE_DIR}
)

target_link_libraries(GraphicsEngine PRIVATE glm::glm)
target_link_libraries(GraphicsEngine PRIVATE spdlog::spdlog_header_only)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
