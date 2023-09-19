CC = g++
CCFLAG = -std=c++17 -g

all : libHbCore.a
	rm *.o

usecasetest : libHbCore.a
	$(CC) $(CCFLAG) test/usecase_test_core.cpp libHbCore.a -o usecasetestdisplay
	rm *.o

libHbCore.a : note_enum_converter.o sci_notename_to_index.o property_enum_converter.o base_duration.o base_note.o base_note_property.o base_voice.o base_bar.o base_sheet.o
	ar cr libHbCore.a note_enum_converter.o sci_notename_to_index.o property_enum_converter.o base_duration.o base_note.o base_note_property.o base_voice.o base_bar.o base_sheet.o

note_enum_converter.o : basetypes/note_enum_converter.hpp
	$(CC) $(CCFLAG) -c basetypes/note_enum_converter.cpp

sci_notename_to_index.o : charts/sci_notename_to_index.hpp
	$(CC) $(CCFLAG) -c charts/sci_notename_to_index.cpp

tempo_enum_converter.o : property/tempo_enum_converter.hpp
	$(CC) $(CCFLAG) -c property/tempo_enum_converter.cpp

property_enum_converter.o : property/property_enum_converter.hpp
	$(CC) $(CCFLAG) -c property/property_enum_converter.cpp

base_duration.o : base_duration.cpp base_duration.hpp
	$(CC) $(CCFLAG) -c base_duration.cpp

base_note.o : base_note.cpp base_note.hpp base_duration.o note_enum_converter.o sci_notename_to_index.o
	$(CC) $(CCFLAG) -c base_note.cpp

base_note_property.o : base_note_property.cpp base_note_property.hpp property_enum_converter.o
	$(CC) $(CCFLAG) -c base_note_property.cpp

base_voice.o : base_voice.cpp base_voice.hpp base_note.o
	$(CC) $(CCFLAG) -c base_voice.cpp

base_bar.o : base_bar.cpp base_bar.hpp base_voice.o
	$(CC) $(CCFLAG) -c base_bar.cpp

base_sheet.o : base_sheet.cpp base_sheet.hpp base_bar.o
	$(CC) $(CCFLAG) -c base_sheet.cpp

clean :
	rm usecasetestdisplay *.a