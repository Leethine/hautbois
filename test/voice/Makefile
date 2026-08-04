CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g -Wall
STATIC_LIBRARY = ../../src/libHb.a
INC_LIBRARY  = -I ../../src

all: test_basicvoice

clean:
	rm -f bin_*

test_basicvoice:
	$(CC) $(CCFLAG) test_basicvoice.cpp $(STATIC_LIBRARY) $(INC_LIBRARY) -o bin_test_basicvoice
