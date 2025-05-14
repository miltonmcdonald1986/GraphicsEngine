enable_testing()
    
find_package(GTest CONFIG REQUIRED)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(GraphicsEngineTests ${TEST_SOURCES})
target_link_libraries(GraphicsEngineTests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
    
include(GoogleTest)
gtest_discover_tests(GraphicsEngineTests)
