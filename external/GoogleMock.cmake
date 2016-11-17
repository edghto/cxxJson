ExternalProject_Add(
    googletest
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external
    GIT_REPOSITORY https://github.com/google/googletest.git
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -Dgtest_force_shared_crt=ON
               -DCMAKE_CXX_FLAGS=-std=c++14 -fpermissive
               -DCMAKE_TOOLCHAIN_FILE:FILEPATH=${CMAKE_TOOLCHAIN_FILE}
               -Wno-dev
    PATCH_COMMAND ""
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(googletest source_dir)
ExternalProject_Get_Property(googletest binary_dir)

set(gmock_source_dir ${source_dir}/googlemock/)
set(gtest_source_dir ${source_dir}/googletest/)
set(gmock_binary_dir ${binary_dir}/googlemock/)

