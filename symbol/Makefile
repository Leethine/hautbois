CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-sign-compare
LINK_LIBRARY = -lboost_serialization
INC_LIBRARY  =  

all : libHbCore.a

clean :
	rm -f unittest_* *.o *.a

libHbCore.a : duration.o pitch.o property.o note_single.o note_group.o note_sequence.o note_chord.o note_tuplet.o
	ar cr libHbCore.a duration.o pitch.o property.o note_single.o note_group.o note_sequence.o note_chord.o note_tuplet.o

duration.o : duration.cpp duration.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) duration.cpp

pitch.o : pitch.cpp pitch.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) pitch.cpp

property.o : property.cpp property.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) property.cpp

note_single.o : note_single.cpp note_single.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) note_single.cpp

note_group.o : note_group.cpp note_group.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) note_group.cpp

note_sequence.o : note_sequence.cpp note_sequence.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) note_sequence.cpp

note_chord.o : note_chord.cpp note_chord.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) note_chord.cpp

note_tuplet.o : note_tuplet.cpp note_tuplet.hpp
	$(CC) $(CCFLAG) -c $(INC_LIBRARY) note_tuplet.cpp

test : test_duration test_pitch test_property test_singlenote

test_duration : libHbCore.a
	$(CC) $(CCFLAG) zzz_test_duration.cpp libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o test_duration

test_pitch : libHbCore.a
	$(CC) $(CCFLAG) zzz_test_pitch.cpp libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o test_pitch

test_property : libHbCore.a
	$(CC) $(CCFLAG) zzz_test_property.cpp libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o test_property

test_singlenote : libHbCore.a
	$(CC) $(CCFLAG) zzz_test_singlenote.cpp libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o test_singlenote

test_chord : libHbCore.a
	$(CC) $(CCFLAG) zzz_test_chord.cpp libHbCore.a $(LINK_LIBRARY) $(INC_LIBRARY) -o test_chord
