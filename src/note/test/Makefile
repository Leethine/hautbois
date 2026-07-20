CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g -Wall
LINK_LIBRARY = 
INC_LIBRARY  = -I ..

all: test_singlenote test_chord

clean:
	rm -f bin_*

test_singlenote:
	$(CC) $(CCFLAG) test_singlenote.cpp ../libHbNote.a ../../symbol/libHbSymbol.a $(LINK_LIBRARY) $(INC_LIBRARY) -o bin_test_singlenote

test_chord:
	$(CC) $(CCFLAG) test_chord.cpp ../libHbNote.a ../../symbol/libHbSymbol.a $(LINK_LIBRARY) $(INC_LIBRARY) -o bin_test_chord
