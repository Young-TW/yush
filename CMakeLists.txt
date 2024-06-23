cmake_minimum_required(VERSION 3.27.0)
project(yush VERSION 0.6.4)

set(CMAKE_CXX_STANDARD 23)

include_directories(./include)

add_subdirectory(cxxopts)
add_subdirectory(fmt)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(YUSH_WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(YUSH_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_compile_definitions(YUSH_MACOS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    add_compile_definitions(YUSH_FREEBSD)
elseif(CMAKE_SYSTEM_NAME STREQUAL "UNIX")
    add_compile_definitions(YUSH_UNIX)
endif()

file(GLOB_RECURSE SRC_FILES ./src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} cxxopts)
target_link_libraries(${PROJECT_NAME} fmt::fmt)

target_compile_definitions(${PROJECT_NAME} PRIVATE YUSH_VERSION="${PROJECT_VERSION}")

install(TARGETS ${PROJECT_NAME})

# enable_testing()

# add_executable(${PROJECT_NAME}_test ./test/test.cpp)
# set(GTEST_MAIN_LIBRARY /opt/homebrew/include/gtest)
# find_package(GTest REQUIRED)
# target_link_libraries(
#   ${PROJECT_NAME}_test
#   GTest::gtest_main
# )

# set_target_properties(GTest::gtest_main PROPERTIES
#     IMPORTED_LOCATION ${GTEST_MAIN_LIBRARY}/libgtest_main.a
# )

# include(GoogleTest)
# gtest_discover_tests(${PROJECT_NAME}_test)
