CC = g++
CCFLAG = -std=c++17 -g

all : property_enum_converter.o tempo_enum_converter.o

property_enum_converter.o : property_enum_converter.hpp property_enum_converter.cpp
	$(CC) $(CCFLAG) -c property_enum_converter.cpp

tempo_enum_converter.o : tempo_enum_converter.hpp tempo_enum_converter.cpp
	$(CC) $(CCFLAG) -c tempo_enum_converter.cpp

clean :
	rm property_enum_converter.o tempo_enum_converter.o