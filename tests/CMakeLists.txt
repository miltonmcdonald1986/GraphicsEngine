enable_testing()

if (WIN32)
	find_package(unofficial-angle REQUIRED CONFIG)
elseif (UNIX)
	find_package(glfw3 CONFIG REQUIRED)
endif()
find_package(GTest CONFIG REQUIRED)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(GraphicsEngineTests ${TEST_SOURCES})

if (WIN32)
	target_link_libraries(GraphicsEngineTests PRIVATE unofficial::angle::libEGL unofficial::angle::libGLESv2)
elseif (UNIX)
	target_link_libraries(GraphicsEngineTests PRIVATE glfw)
endif()
target_link_libraries(GraphicsEngineTests PRIVATE GraphicsEngine GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(GraphicsEngineTests)
