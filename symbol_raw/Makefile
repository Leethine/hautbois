CPPSTD = c++17
CC = g++
CCFLAG = -std=$(CPPSTD) -g -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-sign-compare
LINK_LIBRARY = -lboost_serialization

test :
	$(CC) $(CCFLAG) zzz_test_raw.cpp $(LINK_LIBRARY) -o test_raw

clean :
	rm test_raw cereal_object*