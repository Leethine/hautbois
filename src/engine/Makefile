CC = g++
CPPSTD = c++17
CCFLAGS = -std=$(CPPSTD) -g -Wall -Wextra -Wno-unused-parameter -O2
CCMACROS = -D __HB_PREPROCESSOR_MAIN__
DEPFLAGS = 

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(OBJS:.o=.d)

TARGET := $(OBJS) hb-preprocessor.bin

.PHONY: all clean

all : $(TARGET)

%.o: %.cpp
	$(CC) $(CCFLAGS) $(DEPFLAGS) -c $< -o $@

hb-preprocessor.bin : $(SRCS)
	$(CC) $(CCFLAGS) $(DEPFLAGS) $(CCMACROS) $(SRCS) -o hb-preprocessor.bin

clean :
	rm -f *.o *.bin
