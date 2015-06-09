OUTBIN=fgbdas
CXX=g++
CXXFLAGS=-Wall -Wextra -Wno-unused-parameter -std=c++14 -g -I include -I dependencies/commons/include/
TOLKFILE=dependencies/commons/src/commons/tolkfile
OBJS=src/disassembler.o\
     src/opcodes.o\
     src/main.o\
     ${TOLKFILE}/functable.o\
     ${TOLKFILE}/strtable.o\
     ${TOLKFILE}/symtable.o\
     ${TOLKFILE}/structtable.o\
     ${TOLKFILE}/tolk-file.o

.PHONY: all clean

all: fgbdas

fgbdas: $(OBJS)
	$(CXX) -o $(OUTBIN) $(OBJS)

clean:
	rm -rf $(OBJS) $(OUTBIN)
