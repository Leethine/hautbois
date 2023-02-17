CC = g++
CCFLAG = -std=c++17 -g

usecasetestdisplay : usecase_test_core.cpp base_duration.o base_note.o base_note_property.o
	$(CC) $(CCFLAG) -o usecasetestdisplay usecase_test_core.cpp base_duration.o base_note.o base_note_property.o

base_duration.o : base_duration.cpp base_duration.hpp
	$(CC) $(CCFLAG) -c base_duration.cpp

base_note_property.o : base_note_property.cpp base_note_property.hpp
	$(CC) $(CCFLAG) -c base_note_property.cpp

base_note.o : base_note.cpp base_note.hpp
	$(CC) $(CCFLAG) -c base_note.cpp

clean :
	rm usecasetestdisplay base_duration.o base_note_property.o base_note.o