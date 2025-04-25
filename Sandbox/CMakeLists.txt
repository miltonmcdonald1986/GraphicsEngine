find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(GLOB SANDBOX_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB SANDBOX_APP_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/App/*.h")
file(GLOB SANDBOX_UTILITIES_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/Utilities/*.h")
file(GLOB SANDBOX_WIDGET_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/Widget/*.h")
file(GLOB SANDBOX_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB SANDBOX_APP_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/App/*.cpp")
file(GLOB SANDBOX_UTILITIES_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/Utilities/*.cpp")
file(GLOB SANDBOX_WIDGET_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/Widget/*.cpp")
file(GLOB SANDBOX_SHADERS "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.*")
file(GLOB SANDBOX_TEXTURES "${CMAKE_CURRENT_SOURCE_DIR}/textures/*.*")

file(GLOB SANDBOX_SRC
	${SANDBOX_HEADER_FILES}
	${SANDBOX_APP_HEADER_FILES}
	${SANDBOX_UTILITIES_HEADER_FILES}
	${SANDBOX_WIDGET_HEADER_FILES}
	${SANDBOX_SOURCE_FILES}
	${SANDBOX_APP_SOURCE_FILES}
	${SANDBOX_UTILITIES_SOURCE_FILES}
	${SANDBOX_WIDGET_SOURCE_FILES}
	${SANDBOX_SHADERS}
	${SANDBOX_TEXTURES}
)
source_group("Header Files" FILES ${SANDBOX_HEADER_FILES})
source_group("Header Files/App" FILES ${SANDBOX_APP_HEADER_FILES})
source_group("Header Files/Utilities" FILES ${SANDBOX_UTILITIES_HEADER_FILES})
source_group("Header Files/Widget" FILES ${SANDBOX_WIDGET_HEADER_FILES})
source_group("Source Files" FILES ${SANDBOX_SOURCE_FILES})
source_group("Source Files/App" FILES ${SANDBOX_APP_SOURCE_FILES})
source_group("Source Files/Utilities" FILES ${SANDBOX_UTILITIES_SOURCE_FILES})
source_group("Source Files/Widget" FILES ${SANDBOX_WIDGET_SOURCE_FILES})
source_group("Shaders" FILES ${SANDBOX_SHADERS})
source_group("Textures" FILES ${SANDBOX_TEXTURES})

add_executable(Sandbox ${SANDBOX_SRC})

if(WIN32)
    set_target_properties(Sandbox PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

target_include_directories(Sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/App
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utilities
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Widget
)

target_precompile_headers(Sandbox PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")

target_link_libraries(Sandbox PRIVATE GraphicsEngine)
target_link_libraries(Sandbox PRIVATE glm::glm)
target_link_libraries(Sandbox PRIVATE imgui::imgui)

if (CMAKE_CONFIGURATION_TYPES)
	if (WIN32)
		if (CMAKE_GENERATOR MATCHES "Visual Studio")
			set_property(TARGET Sandbox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>")
			set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
		endif()
	endif()
endif()

set(SHADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
target_compile_definitions(Sandbox PRIVATE SHADERS_DIR="${SHADERS_DIR}")

set(TEXTURES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/textures")
target_compile_definitions(Sandbox PRIVATE TEXTURES_DIR="${TEXTURES_DIR}")
