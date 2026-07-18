CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g -Wall
LINK_LIBRARY = 
INC_LIBRARY  = 

all : libHbSymbol.a

clean :
	rm -f *.o *.a

libHbSymbol.a : duration.o pitch.o property.o
	ar cr libHbSymbol.a duration.o pitch.o property.o

duration.o : duration.cpp duration.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) duration.cpp

pitch.o : pitch.cpp pitch.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) pitch.cpp

property.o : property.cpp property.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) property.cpp
