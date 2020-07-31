#A Makefile for the B-Shell!
CC=gcc
NAME=bsh
TARGET=bin/
SOURCE=./src/
SYS=/bin/
CMDLIBS=$(TARGET)cat.o $(TARGET)cd.o
CMDIR = src/commands/
FLAGS=-O2 -Wall -lm -pedantic -lreadline -o

all: bsh.o bsh_functions.o
	$(CC) $(TARGET)$(NAME).o $(TARGET)$(NAME)_functions.o $(CMDLIBS)   $(FLAGS)  $(NAME)

readline: readline_lib bsh.o
	$(CC) $(TARGET)$(NAME).o $(TARGET)$(NAME)_functions.o $(CMDLIBS)   $(FLAGS)  $(NAME)

readline_lib: $(SOURCE)bsh_functions.c commands
	$(CC) -c -D READLINE $(SOURCE)$(NAME)_functions.c $(FLAGS) $(TARGET)bsh_functions.o

bsh.o: $(SOURCE)bsh.c 
	if [ ! -d $(TARGET) ]; then mkdir bin; fi
	$(CC) -c $(SOURCE)bsh.c $(FLAGS) $(TARGET)bsh.o

bsh_functions.o: $(SOURCE)bsh_functions.c commands
	$(CC) -c $(SOURCE)bsh_functions.c $(FLAGS) $(TARGET)bsh_functions.o

commands:
	$(CC) -c $(CMDIR)cat.c -o $(TARGET)cat.o
	$(CC) -c $(CMDIR)cd.c -o $(TARGET)cd.o

install:
	cp -r $(NAME) $(SYS)
uninstall:
	rm $(SYS)$(NAME)
clean:
	rm $(NAME)
	rm -r $(TARGET)*
