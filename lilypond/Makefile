CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-sign-compare
LINK_LIBRARY = -lboost_serialization
INC_LIBRARY  = -I ../..

all : libHbLilypond.a

clean :
	rm -f unittest_* *.o *.a

libHbLilypond.a : ly_duration.o ly_pitch.o ly_property.o ly_singlenote.o ly_chord.o ly_tuplet.o 
	ar cr libHbLilypond.a ly_duration.o ly_pitch.o ly_property.o ly_singlenote.o ly_chord.o ly_tuplet.o

ly_duration.o : ly_duration.cpp ly_duration.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) ly_duration.cpp

ly_pitch.o : ly_pitch.cpp ly_pitch.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) ly_pitch.cpp

ly_property.o : ly_property.cpp ly_property.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) ly_property.cpp

ly_singlenote.o : ly_singlenote.cpp ly_singlenote.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) ly_singlenote.cpp

ly_chord.o : ly_chord.cpp ly_chord.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) ly_chord.cpp

ly_tuplet.o : ly_tuplet.cpp ly_tuplet.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) ly_tuplet.cpp
