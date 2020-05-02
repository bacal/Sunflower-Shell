#A Makefile for the B-Shell!
CC=gcc
TARGET=bsh
FLAGS=-Wall -lm -pedantic -o
all:
	$(CC) $(TARGET).c $(TARGET)_functions.c $(FLAGS) $(TARGET)
clean:
	rm $(TARGET)
