cmake_minimum_required (VERSION 2.6)
project (TestExpr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g ")

set (CMAKE_BINARY_DIR "./output")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# The version number.
set (TestExpr_VERSION_MAJOR 1)
set (TTestExpr_VERSION_MINOR 0)

# FILE(GLOB parsersrc parsers/error.cpp parsers/functions.cpp parsers/variablelist.cpp parsers/parser.cpp)
# add_executable(TestParser parsers/main.cpp ${parsersrc})


#add_library(parser STATIC IMPORTED)
#set_property(TARGET parser PROPERTY IMPORTED_LOCATION ./parsers/parser.a)


FILE(GLOB expr_src expr/*.cpp)
#add_library(expr ${expr_src})

FILE(GLOB parser_src parsers/calc.tab.cpp parsers/parser_utils.cpp parsers/lex.yy.c)
#add_library(parser ${parser_src})

add_executable(TestExpr test.cpp create_matrix_exp.cpp ${expr_src} ${parser_src})

#target_link_libraries(TextExpr parser)
#target_link_libraries(TestExpr expr)



