cmake_minimum_required(VERSION 3.0.0)
project(yush VERSION 0.1.0)

# include(CTest)
# enable_testing()

# if windows
# add_compile_options(/std:c++17)

include_directories(.)

add_executable(yush ./src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)