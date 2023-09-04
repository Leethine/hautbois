CC = g++
CCFLAG = -std=c++17 -g

all : base_duration.o base_note.o base_note_property.o base_voice.o

usecasetest : test/usecase_test_core.cpp base_duration.o base_note.o base_note_property.o base_voice.o base_bar.o
	$(CC) $(CCFLAG) -o usecasetestdisplay test/usecase_test_core.cpp basetypes/note_enum_converter.o charts/sci_notename_to_index.o property/property_enum_converter.o base_duration.o base_note.o base_note_property.o base_voice.o base_bar.o

base_duration.o : base_duration.cpp base_duration.hpp
	$(CC) $(CCFLAG) -c base_duration.cpp

base_note.o : base_note.cpp base_note.hpp base_duration.o basetypes/note_enum_converter.o charts/sci_notename_to_index.o
	$(CC) $(CCFLAG) -c base_note.cpp

base_note_property.o : base_note_property.cpp base_note_property.hpp property/property_enum_converter.o
	$(CC) $(CCFLAG) -c base_note_property.cpp

base_voice.o : base_voice.cpp base_voice.hpp base_note.o
	$(CC) $(CCFLAG) -c base_voice.cpp

base_bar.o : base_bar.cpp base_bar.hpp base_voice.o
	$(CC) $(CCFLAG) -c base_bar.cpp

clean :
	rm usecasetestdisplay base_duration.o base_note_property.o base_note.o base_voice.o base_bar.o charts/sci_notename_to_index.o basetypes/note_enum_converter.o property/property_enum_converter.o property/tempo_enum_converter.o