cmake_minimum_required(VERSION 3.10)
project(GraphicsEngine)

include("${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
	string(REPLACE "/W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	add_compile_options(/W4 /WX)
else()
	add_compile_options(-Wall -Wextra -Werror -Wno-unknown-pragmas)
endif()

add_subdirectory(GraphicsEngine)
add_subdirectory(Sandbox)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
install(TARGETS GraphicsEngine Sandbox DESTINATION "$<CONFIG>")
install(FILES $<TARGET_RUNTIME_DLLS:GraphicsEngine> DESTINATION "$<CONFIG>")
install(FILES "${CMAKE_BINARY_DIR}/GraphicsEngine/$<CONFIG>/GraphicsEngine.pdb" DESTINATION "$<CONFIG>")
install(FILES $<TARGET_RUNTIME_DLLS:Sandbox> DESTINATION "$<CONFIG>")
install(DIRECTORY "${CMAKE_SOURCE_DIR}/Sandbox/shaders" DESTINATION "$<CONFIG>")
install(DIRECTORY "${CMAKE_SOURCE_DIR}/Sandbox/textures" DESTINATION "$<CONFIG>")
set_property(TARGET Sandbox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}/$<CONFIG>")
set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)
