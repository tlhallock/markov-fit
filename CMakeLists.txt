cmake_minimum_required (VERSION 2.6)
project (TestDirect)

#target_compile_features(TestDirect PRIVATE cxx_range_for)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g ")


# SET(CMAKE_C_COMPILER mex)
# SET(CMAKE_CXX_COMPILER mex)



# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)


include_directories(${PROJECT_SOURCE_DIR})

add_library(ransample alias/ransampl.c)
 

# add the executable
#add_library(Test test.cpp generator.cpp )
add_executable(Test test.cpp args.cpp markov.cpp cdf.cpp local/local_search_params.cpp local/local_search.cpp generator.cpp)
target_link_libraries(Test ransample)

# matlab/matrix_exp.cpp

