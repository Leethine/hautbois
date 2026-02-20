CC = g++
CCFLAG = -std=c++17 -g
LINK_LIBRARY = -lboost_unit_test_framework -lboost_serialization

test :
	$(CC) $(CCFLAG) ZZZ_TEST_raw.cpp $(LINK_LIBRARY) -o unittest

clean :
	rm unittest serial_object*