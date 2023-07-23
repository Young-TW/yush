cmake_minimum_required(VERSION 3.0.0)
project(yush VERSION 0.2.0)

set(CMAKE_CXX_STANDARD 23)

include_directories(./include)

add_subdirectory(cxxopts)
add_subdirectory(fmt)

file(GLOB_RECURSE SRC_FILES ./src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE cxxopts)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt)

install(TARGETS ${PROJECT_NAME})