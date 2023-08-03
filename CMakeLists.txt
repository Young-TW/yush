cmake_minimum_required(VERSION 3.0.0)
project(yush VERSION 0.4.2)

set(CMAKE_CXX_STANDARD 23)

include_directories(./include)

add_subdirectory(cxxopts)
add_subdirectory(fmt)

file(GLOB_RECURSE SRC_FILES ./src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} cxxopts)
target_link_libraries(${PROJECT_NAME} fmt::fmt)

install(TARGETS ${PROJECT_NAME})