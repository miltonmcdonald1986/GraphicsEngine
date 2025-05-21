enable_testing()

find_package(EGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(GraphicsEngineTests ${TEST_SOURCES})

target_link_libraries(GraphicsEngineTests PRIVATE GraphicsEngine unofficial::mesa::libEGL unofficial::mesa::libGLESv2 glfw GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(GraphicsEngineTests)
