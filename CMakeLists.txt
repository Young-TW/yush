cmake_minimum_required(VERSION 3.27.0)
project(yush VERSION 0.6.4)

set(CMAKE_CXX_STANDARD 23)

include_directories(./include)

add_subdirectory(cxxopts)
add_subdirectory(fmt)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(YUSH_LINUX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_compile_definitions(YUSH_MACOS)
elseif (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    add_compile_definitions(YUSH_FREEBSD)
elseif (CMAKE_SYSTEM_NAME STREQUAL "UNIX")
    add_compile_definitions(YUSH_UNIX)
endif ()

file(GLOB_RECURSE SRC_FILES ./src/*.cpp)
list(REMOVE_ITEM SRC_FILES "src/main.cpp")

add_library(${PROJECT_NAME}_lib STATIC ${SRC_FILES})
target_link_libraries(${PROJECT_NAME}_lib cxxopts fmt::fmt)
target_compile_definitions(${PROJECT_NAME}_lib PUBLIC YUSH_VERSION="${PROJECT_VERSION}")

add_executable(${PROJECT_NAME} "src/main.cpp")
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

install(TARGETS ${PROJECT_NAME})

enable_testing()

file(GLOB_RECURSE TEST_FILES ./test/*.cpp)
add_executable(${PROJECT_NAME}_test ${TEST_FILES})
find_package(GTest REQUIRED)

target_link_libraries(${PROJECT_NAME}_test GTest::gtest_main)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
