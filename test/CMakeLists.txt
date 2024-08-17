file(GLOB_RECURSE TEST_FILES *.cpp)

add_executable(${PROJECT_NAME}_test ${TEST_FILES})
target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest_main PRIVATE ${PROJECT_NAME}_lib)
gtest_discover_tests(${PROJECT_NAME}_test)
