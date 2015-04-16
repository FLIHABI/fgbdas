OUTBIN=fgbdas
CXX=g++
CXXFLAGS=-Wall -Wextra -Wno-unused-parameter -std=c++14 -g -I include -I dependencies/commons/include/
OBJS=src/disassembler.o\
     src/opcodes.o\
     main.o

.PHONY: all clean

all: fgbdas

fgbdas: $(OBJS)
	$(CXX) -o $(OUTBIN) $(OBJS)

clean:
	rm -rf $(OBJS) $(OUTBIN)
