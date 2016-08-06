project(cxxJson)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++14 -ggdb3 -O0)

include(ExternalProject)
include(external/GoogleMock.cmake)

include_directories(include)
add_subdirectory(test)


