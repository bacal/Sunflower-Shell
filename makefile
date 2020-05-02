#A Makefile for the B-Shell!
CC=gcc
WINCC=i686-w64-mingw32-gcc
TARGET=bsh
FLAGS=-Wall -lm -pedantic -o
all:
	$(CC) $(TARGET).c $(TARGET)_functions.c $(FLAGS) $(TARGET)
win:
	$(WINCC) $(TARGET).c $(TARGET)_functions.c $(FLAGS) $(TARGET).exe
clean:
	rm $(TARGET)
