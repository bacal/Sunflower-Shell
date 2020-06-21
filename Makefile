#A Makefile for the B-Shell!
CC=gcc
NAME=bsh
TARGET=bin/
SOURCE=./src/
SYS=/bin/
FLAGS=-O0 -Wall -lm -pedantic -lreadline -o

all: bsh.o bsh_predefined.o bsh_functions.o
	$(CC) $(TARGET)$(NAME).o $(TARGET)$(NAME)_predefined.o $(TARGET)$(NAME)_functions.o $(FLAGS) $(NAME)


bsh.o: $(SOURCE)bsh.c
	if [ ! -d $(TARGET) ]; then mkdir bin; fi
	$(CC) -c $(SOURCE)bsh.c $(FLAGS) $(TARGET)bsh.o
bsh_predefined.o: $(SOURCE)bsh_predefined.c
	$(CC) -c $(SOURCE)bsh_predefined.c $(FLAGS) $(TARGET)bsh_predefined.o
bsh_functions.o:	$(SOURCE)bsh_functions.c
	$(CC) -c $(SOURCE)bsh_functions.c $(FLAGS) $(TARGET)bsh_functions.o
install:
	cp -r $(NAME) $(SYS)
uninstall:
	rm $(SYS)$(NAME)
clean:
	rm $(NAME)
	rm -rf $(TARGET)*
