CC = g++
CPPSTD = c++17
CCFLAGS = -std=$(CPPSTD) -g 
DEPFLAGS = ../src/libHb.a -lm -lasound -lstk

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=bin_%)

TARGET := $(OBJS)

.PHONY: all clean

all : $(OBJS)
	for bin in $(OBJS); do \
		./$$bin clean;       \
	done

bin_%: %.cpp
	$(CC) $(CCFLAGS) $< $(DEPFLAGS) -o $@


clean :
	rm -f bin_* *.wav
