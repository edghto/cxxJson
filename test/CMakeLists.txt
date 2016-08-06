project(cxxJson)
cmake_minimum_required(VERSION 2.8)


include_directories(include .)

include_directories(${gmock_source_dir}/include)
include_directories(${gmock_source_dir}/gtest/include)
link_directories(${gmock_binary_dir})

file(GLOB_RECURSE TEST_SRC *.cpp *.hpp ../include/*.hpp)
add_executable(${PROJECT_NAME}-test ${TEST_SRC})
target_link_libraries(${PROJECT_NAME}-test
    gmock
    gmock_main
    pthread)



