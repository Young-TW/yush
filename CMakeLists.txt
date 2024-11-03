cmake_minimum_required(VERSION 3.27.0)
project(yush VERSION 0.6.5)

include(CTest)

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

if (BUILD_TESTING)
    find_package(GTest REQUIRED)
    add_subdirectory(test)
endif ()
