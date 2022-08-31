#!/bin/sh

if [ -f unittestdisplay ]; then
    rm unittestdisplay
fi

g++ -ounittestdisplay -std=c++17 -lboost_unit_test_framework test_one_voice.cpp
./unittestdisplay

if [ -f unittestdisplay ]; then
    rm unittestdisplay
fi
