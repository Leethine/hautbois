CC = g++
CCFLAG = -std=c++17 -g

all : sci_notename_to_index.o

sci_notename_to_index.o : sci_notename_to_index.cpp sci_notename_to_index.hpp chart_def_types.hpp
	$(CC) $(CCFLAG) -c sci_notename_to_index.cpp

clean:
	rm sci_notename_to_index.o chart_def_types.o
