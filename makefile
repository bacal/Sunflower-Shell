#A Makefile for the B-Shell!
CC=gcc
NAME=bsh
TARGET=./bin/
SOURCE=./source/
SYS=/bin/
FLAGS=-Wall -lm -pedantic -o

bsh: bsh.o bsh_predefined.o bsh_functions.o
	$(CC) $(TARGET)$(NAME).o $(TARGET)$(NAME)_predefined.o $(TARGET)$(NAME)_functions.o $(FLAGS) $(NAME)
bsh.o: $(SOURCE)bsh.c
	$(CC) -c $(SOURCE)bsh.c
	mv bsh.o $(TARGET)
bsh_predefined.o: $(SOURCE)bsh_predefined.c
	$(CC) -c $(SOURCE)bsh_predefined.c
	mv bsh_predefined.o bin/
bsh_functions.o:	$(SOURCE)bsh_functions.c
	$(CC) -c $(SOURCE)bsh_functions.c
	mv bsh_functions.o bin/
install:
	cp -r $(NAME) $(SYS)
uninstall:
	rm $(SYS)$(NAME)
clean:
	rm $(NAME)
	rm $(TARGET)*
