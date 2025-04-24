find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(GLOB_RECURSE SANDBOX_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

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
