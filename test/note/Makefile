CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g -Wall
STATIC_LIBRARY = ../../src/libHb.a
INC_LIBRARY  = -I ../../src

all: test_singlenote test_chord test_gracenote test_tuplet

clean:
	rm -f bin_*

test:
	

test_singlenote:
	$(CC) $(CCFLAG) test_singlenote.cpp $(STATIC_LIBRARY) $(INC_LIBRARY) -o bin_test_singlenote

test_chord:
	$(CC) $(CCFLAG) test_chord.cpp $(STATIC_LIBRARY) $(INC_LIBRARY) -o bin_test_chord

test_gracenote:
	$(CC) $(CCFLAG) test_gracenote.cpp $(STATIC_LIBRARY) $(INC_LIBRARY) -o bin_test_gracenote

test_tuplet:
	$(CC) $(CCFLAG) test_tuplet.cpp $(STATIC_LIBRARY) $(INC_LIBRARY) -o bin_test_tuplet