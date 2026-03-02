CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g
LINK_LIBRARY = -lboost_unit_test_framework -lboost_serialization
INC_LIBRARY  = -I ../..

all : duration.o property.o

test : duration.o property.o
	echo "TODO"

clean :
	rm -f unittest_* *.o *.a

duration.o : duration.cpp duration.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) duration.cpp

property.o : property.cpp property.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) property.cpp
