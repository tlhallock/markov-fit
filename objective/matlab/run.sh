#!/bin/bash




cd /home/default/Documents/Source/C/fit
cmake .
make
cd /home/default/Documents/Source/C/fit/matlab
mex -v -client engine matrix_exp.cpp  ../libTest.a
LD_LIBRARY_PATH=/usr/local/MATLAB/R2015a/bin/glnxa64/ ./matrix_exp 
