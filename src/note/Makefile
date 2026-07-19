CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g -Wall
LINK_LIBRARY = 
INC_LIBRARY  = 

all : libHbNote.a

clean :
	rm -f *.o *.a

libHbNote.a : note.o single_note.o
	ar cr libHbNote.a note.o single_note.o

note.o : note.cpp note.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) note.cpp

single_note.o : single_note.cpp single_note.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) single_note.cpp
