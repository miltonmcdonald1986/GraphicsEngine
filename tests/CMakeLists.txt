enable_testing()

find_package(glfw3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(unofficial-angle REQUIRED CONFIG)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(GraphicsEngineTests ${TEST_SOURCES})
target_link_libraries(GraphicsEngineTests PRIVATE GraphicsEngine glfw unofficial::angle::libEGL unofficial::angle::libGLESv2 GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
include(GoogleTest)
gtest_discover_tests(GraphicsEngineTests)
