CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g
LINK_LIBRARY = -lboost_unit_test_framework -lboost_serialization
INC_LIBRARY  = -I ../../..

all : pitch.o note.o

test : pitch.o note.o
	echo "TODO"

clean :
	rm -f unittest_* *.o *.a

pitch.o : pitch.cpp pitch.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) pitch.cpp

note.o : note.cpp note.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) note.cpp
