CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g -Wall
LINK_LIBRARY = 
INC_LIBRARY  = -I ..

all: test_duration test_pitch test_property

clean:
	rm -f bin_*

test_duration:
	$(CC) $(CCFLAG) test_duration.cpp ../libHbSymbol.a $(LINK_LIBRARY) $(INC_LIBRARY) -o bin_test_duration

test_pitch:
	$(CC) $(CCFLAG) test_pitch.cpp ../libHbSymbol.a $(LINK_LIBRARY) $(INC_LIBRARY) -o bin_test_pitch

test_property:
	$(CC) $(CCFLAG) test_property.cpp ../libHbSymbol.a $(LINK_LIBRARY) $(INC_LIBRARY) -o bin_test_property