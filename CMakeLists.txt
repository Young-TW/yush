cmake_minimum_required(VERSION 3.27.0)
project(yush VERSION 0.6.4)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(cxxopts)
add_subdirectory(fmt)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_library(${PROJECT_NAME}_lib STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC include/)
target_link_libraries(${PROJECT_NAME}_lib PUBLIC cxxopts PUBLIC fmt::fmt)
target_compile_definitions(${PROJECT_NAME}_lib PUBLIC YUSH_VERSION="${PROJECT_VERSION}")
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(${PROJECT_NAME}_lib PUBLIC YUSH_LINUX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME}_lib PUBLIC YUSH_MACOS)
elseif (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    target_compile_definitions(${PROJECT_NAME}_lib PUBLIC YUSH_FREEBSD)
elseif (CMAKE_SYSTEM_NAME STREQUAL "UNIX")
    target_compile_definitions(${PROJECT_NAME}_lib PUBLIC YUSH_UNIX)
endif ()

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

install(TARGETS ${PROJECT_NAME})

enable_testing()

file(GLOB_RECURSE TEST_FILES test/*.cpp)
add_executable(${PROJECT_NAME}_test ${TEST_FILES})
find_package(GTest REQUIRED)

target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest_main PRIVATE ${PROJECT_NAME}_lib)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
