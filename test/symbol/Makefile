CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g -Wall
STATIC_LIBRARY = ../../src/libHb.a
INC_LIBRARY  = -I ../../src

all: test_duration test_pitch test_property

clean:
	rm -f bin_*

test_duration:
	$(CC) $(CCFLAG) test_duration.cpp $(STATIC_LIBRARY) $(INC_LIBRARY) -o bin_test_duration

test_pitch:
	$(CC) $(CCFLAG) test_pitch.cpp $(STATIC_LIBRARY) $(INC_LIBRARY) -o bin_test_pitch

test_property:
	$(CC) $(CCFLAG) test_property.cpp $(STATIC_LIBRARY) $(INC_LIBRARY) -o bin_test_property