cmake_minimum_required (VERSION 2.6)
project (TestDirect)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g ")

set (CMAKE_BINARY_DIR "./output")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# The version number.
set (TestDirect_VERSION_MAJOR 1)
set (TestDirect_VERSION_MINOR 0)


include_directories(${PROJECT_SOURCE_DIR} /usr/include/gsl/)

add_library(ransample alias/ransampl.c)
add_library(markov markov/mexp.cpp markov/generator.cpp markov/markov_chain.cpp markov/markov_simulator.cpp) 
add_library(stats stats/cdf.cpp)
add_library(local local/local_search_params.cpp local/local_search.cpp)


add_executable(TestDirect test.cpp )

target_link_libraries(TestDirect stats)
target_link_libraries(TestDirect local)
target_link_libraries(TestDirect markov)
target_link_libraries(TestDirect ransample)
target_link_libraries(TestDirect gsl gslcblas)




#target_compile_features(TestDirect PRIVATE cxx_range_for)
# add_executable(TestExpM matrix_exp/matrix_exponential.c matrix_exp/r8lib.c matrix_exp/c8lib.c)
# target_link_libraries(TestExpM m)
#add_executable(TestExpM matrix_exp/c8lib.cpp  matrix_exp/matrix_exponential.cpp  matrix_exp/matrix_exponential_prb.cpp  matrix_exp/r8lib.cpp  )
# SET(CMAKE_C_COMPILER mex)
# SET(CMAKE_CXX_COMPILER mex)