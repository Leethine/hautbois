#!/bin/sh

if [ -f unittestdisplay ]; then
    rm unittestdisplay
fi

g++ -ounittestdisplay -std=c++14 -lboost_unit_test_framework test_duration.cpp
./unittestdisplay

g++ -ounittestdisplay -std=c++17 -lboost_unit_test_framework test_one_note_base.cpp
./unittestdisplay

g++ -ounittestdisplay -std=c++17 -lboost_unit_test_framework test_one_note_mono.cpp
./unittestdisplay

g++ -ounittestdisplay -std=c++17 -lboost_unit_test_framework test_one_note_rest.cpp
./unittestdisplay

g++ -ounittestdisplay -std=c++17 -lboost_unit_test_framework test_one_note_chord.cpp
./unittestdisplay

g++ -ounittestdisplay -std=c++17 -lboost_unit_test_framework test_one_note_tuplet.cpp
./unittestdisplay

if [ -f unittestdisplay ]; then
    rm unittestdisplay
fi
