CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g
LINK_LIBRARY = -lboost_unit_test_framework -lboost_serialization
INC_LIBRARY  = -I ..

all : libHbCore.a

test : libHbCore.a
	$(CC) $(CCFLAG) ZZZ_TEST_duration.cpp libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o unittest_duration
	$(CC) $(CCFLAG) ZZZ_TEST_pitch.cpp    libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o unittest_pitch
	$(CC) $(CCFLAG) ZZZ_TEST_property.cpp libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o unittest_property
	$(CC) $(CCFLAG) ZZZ_TEST_note.cpp     libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o unittest_note

clean :
	rm unittest_* *.o *.a

libHbCore.a : duration.o pitch.o property.o note.o
	ar cr libHbCore.a duration.o pitch.o property.o note.o

duration.o : duration.cpp duration.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) duration.cpp

pitch.o : pitch.cpp pitch.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) pitch.cpp

property.o : property.cpp property.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) property.cpp

note.o : note.cpp note.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) note.cpp