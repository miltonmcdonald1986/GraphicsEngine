enable_testing()
    
find_package(GTest CONFIG REQUIRED)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(GraphicsEngineTests ${TEST_SOURCES})
target_link_libraries(GraphicsEngineTests PRIVATE GraphicsEngine GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
    
# Enable coverage options based on compiler
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(unit_tests PRIVATE -fprofile-arcs -ftest-coverage)
    target_link_options(unit_tests PRIVATE -lgcov)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(unit_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(unit_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
endif()

include(GoogleTest)
gtest_discover_tests(GraphicsEngineTests)
