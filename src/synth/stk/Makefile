CC = g++
CPPSTD = c++17
CCFLAGS = -std=$(CPPSTD) -g -Wall -Wextra -Wno-unused-parameter -O2
DEPFLAGS = 

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(OBJS:.o=.d)

TARGET := $(OBJS)

.PHONY: all clean

all : $(OBJS)

%.o: %.cpp
	$(CC) $(CCFLAGS) $(DEPFLAGS) -c $< -o $@

clean :
	rm -f *.o
