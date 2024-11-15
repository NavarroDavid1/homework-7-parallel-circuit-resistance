.PHONY: build
build: main

.PHONY: clean
clean:
	rm -f main $(OBJECTS)

# Compiler settings
CXX=g++
CC=gcc
ASM=nasm
CXXFLAGS=-Wall -g -no-pie
ASMFLAGS=-f elf64
LDFLAGS=-no-pie

# Object files
OBJECTS=ohm.o resistance.o get_resistance.o compute_resistance.o show_resistance.o

# Main target
main: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o main $(OBJECTS)

# Individual object targets
ohm.o: ohm.cpp
	$(CXX) $(CXXFLAGS) -c ohm.cpp

resistance.o: resistance.asm
	$(ASM) $(ASMFLAGS) resistance.asm

get_resistance.o: get_resistance.c
	$(CC) -c get_resistance.c

compute_resistance.o: compute_resistance.cpp
	$(CXX) $(CXXFLAGS) -c compute_resistance.cpp

show_resistance.o: show_resistance.cpp
	$(CXX) $(CXXFLAGS) -c show_resistance.cpp
