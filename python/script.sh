#!/bin/bash
cd test
python setup.py build_ext --inplace
cp _chi2.so ..
cd -
