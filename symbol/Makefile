CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g
LINK_LIBRARY = -lboost_unit_test_framework -lboost_serialization
INC_LIBRARY  = -I ..

all : libHbCore.a

clean :
	rm -f unittest_* *.o *.a

libHbCore.a : duration.o pitch.o property.o note_single.o
	ar cr libHbCore.a duration.o pitch.o property.o note_single.o

duration.o : duration.cpp duration.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) duration.cpp

pitch.o : pitch.cpp pitch.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) pitch.cpp

property.o : property.cpp property.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) property.cpp

note_single.o : note_single.cpp note_single.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) note_single.cpp

test : libHbCore.a unittest_duration unittest_pitch unittest_property unittest_note_single

unittest_duration : libHbCore.a
	$(CC) $(CCFLAG) ZZZ_TEST_duration.cpp libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o unittest_duration

unittest_pitch : libHbCore.a
	$(CC) $(CCFLAG) ZZZ_TEST_pitch.cpp libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o unittest_pitch

unittest_property : libHbCore.a
	$(CC) $(CCFLAG) ZZZ_TEST_property.cpp libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o unittest_property

unittest_note_single : libHbCore.a
	$(CC) $(CCFLAG) ZZZ_TEST_note_single.cpp libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o unittest_note_single
