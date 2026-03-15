CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g
LINK_LIBRARY = -lboost_unit_test_framework -lboost_serialization
INC_LIBRARY  = -I ../..

all : libHbAdapter.a

clean :
	rm -f unittest_* *.o *.a

libHbAdapter.a : ly_duration.o ly_pitch.o ly_property.o
	ar cr libHbAdapter.a ly_duration.o ly_pitch.o ly_property.o

ly_duration.o : ly_duration.cpp ly_duration.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) ly_duration.cpp

ly_pitch.o : ly_pitch.cpp ly_pitch.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) ly_pitch.cpp

ly_property.o : ly_property.cpp ly_property.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) ly_property.cpp
