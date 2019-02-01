# File: Makefile
# Date: 02/01/19
# Author: Chris Humphreys
#   -> Adapted from Makefile by Joshua Geurin
# Description: Makefile for C assignment in CS485

# Compiler Version
CC=gcc

# Debugging flag -g
DEBUG=-g

# Memory Mangagment Flags
MEMFLAGS=-fsanitize=address -fno-omit-frame-pointer

# Target
TARGET=threads

# Compile with all errors and warnings
CFLAGS=-c -Wall $(DEBUG)

# Makefile syntax:
# target: dependencies
#(tab) system command(s)

all: $(TARGET)

$(TARGET): main.c
	$(CC) main.c -o $(TARGET) $(DEBUG) $(MEMFLAGS)

threads.o: threads.c threads.h
	$(CC) $(CFLAGS) $(MEMFLAGS) threads.h

# graph.o: graph.h graph.c stack.o
# 	$(CC) $(CFLAGS) $(MEMFLAGS) graph.h

# stack.o: stack.h stack.c
# 	$(CC) $(CFLAGS) $(MEMFLAGS) stack.h

clean:
	rm -f *.o *~ *.swp *.gch $(TARGET)
