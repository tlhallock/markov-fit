cmake_minimum_required (VERSION 2.6)
project (TestExpr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g ")

set (CMAKE_BINARY_DIR "./output")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# The version number.
set (TestDirect_VERSION_MAJOR 1)
set (TestDirect_VERSION_MINOR 0)



FILE(GLOB expr_src expr/*.cpp)

add_library(expr ${expr_src})

add_executable(TestExpr test.cpp)

target_link_libraries(TestExpr expr)


