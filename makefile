#A Makefile for the B-Shell!
CC=gcc
TARGET=bsh
FLAGS=-Wall -lm -pedantic -o
bsh: bsh.o bsh_predefined.o bsh_functions.o
	$(CC) bin/$(TARGET).o bin/$(TARGET)_predefined.o bin/$(TARGET)_functions.o $(FLAGS) $(TARGET)
bsh.o: source/bsh.c
	$(CC) -c source/bsh.c
	mv bsh.o bin/
bsh_predefined.o: source/bsh_predefined.c
	$(CC) -c source/bsh_predefined.c
	mv bsh_predefined.o bin/
bsh_functions.o:	source/bsh_functions.c
	$(CC) -c source/bsh_functions.c
	mv bsh_functions.o bin/
clean:
	rm $(TARGET)
	rm -rf bin/*
