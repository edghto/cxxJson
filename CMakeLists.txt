project(cxxJson)
cmake_minimum_required(VERSION 2.8)


#include(ExternalProject)
#include(external/GoogleMock.cmake)


file(GLOB_RECURSE SRC_LIST *.cpp *.hpp)

include_directories(include)
add_definitions(-std=c++14 -ggdb3 -O0)
add_executable(${PROJECT_NAME} ${SRC_LIST})

