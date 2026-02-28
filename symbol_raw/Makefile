CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g
LINK_LIBRARY = -lboost_unit_test_framework -lboost_serialization

test :
	$(CC) $(CCFLAG) ZZZ_TEST_raw.cpp $(LINK_LIBRARY) -o unittest

clean :
	rm unittest cereal_object*