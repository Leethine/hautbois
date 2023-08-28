CC = g++
CCFLAG = -std=c++17 -g

usecasetestdisplay : test/usecase_test_core.cpp base_duration.o base_note.o base_note_property.o base_voice.o
	$(CC) $(CCFLAG) -o usecasetestdisplay test/usecase_test_core.cpp basetypes/note_enum_converter.o charts/sci_notename_to_index.o base_duration.o base_note.o base_note_property.o base_voice.o

base_voice.o : base_voice.cpp base_voice.hpp base_note.o
	$(CC) $(CCFLAG) -c base_voice.cpp

base_note.o : base_note.cpp base_note.hpp base_duration.o basetypes/note_enum_converter.o charts/sci_notename_to_index.o
	$(CC) $(CCFLAG) -c base_note.cpp

base_duration.o : base_duration.cpp base_duration.hpp
	$(CC) $(CCFLAG) -c base_duration.cpp

base_note_property.o : base_note_property.cpp base_note_property.hpp
	$(CC) $(CCFLAG) -c base_note_property.cpp

clean :
	rm usecasetestdisplay base_duration.o base_note_property.o base_note.o base_voice.o charts/sci_notename_to_index.o basetypes/note_enum_converter.o