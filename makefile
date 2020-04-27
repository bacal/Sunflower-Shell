#A Makefile for the B(acal) Shell!
CC=gcc
TARGET=bsh
FLAGS=-Wall -pedantic -o 
all:
	$(CC) $(TARGET).c $(FLAGS) $(TARGET)
clean:
	rm $(TARGET)
