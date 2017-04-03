# File: Makefile
# Author: Matthew Leeds

CC=clang++
CFLAGS=-g -Wall -std=c++11
OBJ=main.o Matrix.o

.PHONY: clean

math410: $(OBJ)
	$(CC) $(CFLAGS) -o math410 $(OBJ)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Matrix.o: Matrix.cpp
	$(CC) $(CFLAGS) -c Matrix.cpp

clean:
	-rm hillcipher *.o
