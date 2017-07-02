project(cxxJson)
cmake_minimum_required(VERSION 2.8)


include_directories(include .)

include_directories(${gmock_source_dir}/include)
include_directories(${gtest_source_dir}/include)
link_directories(${gmock_binary_dir})

add_definitions(-DWITH_BOOSTPTREE)

file(GLOB_RECURSE TEST_SRC *.cpp *.hpp ../include/*.hpp)
add_executable(${PROJECT_NAME}-test ${TEST_SRC})
target_link_libraries(${PROJECT_NAME}-test
    gmock
    gmock_main
    pthread)



