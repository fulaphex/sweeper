CC = g++
CXXFLAGS = -O2 -Wall -W -Wshadow -Wuninitialized -Wconversion -Wformat -std=c++11
TARGETS = Main

all: $(TARGETS)

Main: Board.o Search.o Eval.o Parser.o

Search: Board.o

Eval: Board.o

Parser: Board.o

clean:
	rm -f *.o

distclean: clean
	rm -f $(TARGETS)
