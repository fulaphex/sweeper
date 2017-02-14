CC = g++
CXXFLAGS = -O2 -Wall -W -Wshadow -Wuninitialized -Wconversion -Wformat -std=c++11
TARGETS = Board

all: $(TARGETS)

Board: 0x88_math.h

clean:
	rm -f *.o

distclean: clean
	rm -f $(TARGETS)