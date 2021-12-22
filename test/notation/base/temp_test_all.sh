#!/bin/sh

if [ -f unittestdisplay ]; then
    rm unittestdisplay
fi

g++ -ounittestdisplay -std=c++14 -lboost_unit_test_framework test_base_optional_boost.cpp
./unittestdisplay

g++ -ounittestdisplay -std=c++17 -lboost_unit_test_framework test_base_optional_cpp17.cpp
./unittestdisplay

g++ -ounittestdisplay -std=c++17 -lboost_unit_test_framework test_syntax_regexp.cpp
./unittestdisplay

if [ -f unittestdisplay ]; then
    rm unittestdisplay
fi
