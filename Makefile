#A Makefile for the B-Shell!
CC=gcc
NAME=bsh
LIBS=lib/
SOURCE=./src/
SYS=usr/bin/
CMDLIBS=$(LIBS)cat.o $(LIBS)cd.o
CMDIR = src/commands/
FLAGS=-O2 -Wall -lm -pedantic -lreadline -o

all: bsh.o bsh_functions.o
	if [ ! -d $(SYS) ]; then mkdir usr/ mkdir $(SYS); fi
	$(CC) $(LIBS)$(NAME).o $(LIBS)$(NAME)_functions.o $(CMDLIBS)   $(FLAGS)  $(SYS)$(NAME)

readline: readline_lib bsh.o
	$(CC) $(LIBS)$(NAME).o $(LIBS)$(NAME)_functions.o $(CMDLIBS)   $(FLAGS)  $(SYS)$(NAME)

readline_lib: $(SOURCE)bsh_functions.c commands
	$(CC) -c -D READLINE $(SOURCE)$(NAME)_functions.c $(FLAGS) $(LIBS)bsh_functions.o

bsh.o: $(SOURCE)bsh.c 
	if [ ! -d $(LIBS) ]; then mkdir $(LIBS); fi
	$(CC) -c $(SOURCE)bsh.c $(FLAGS) $(LIBS)bsh.o

bsh_functions.o: $(SOURCE)bsh_functions.c commands
	$(CC) -c $(SOURCE)bsh_functions.c $(FLAGS) $(LIBS)bsh_functions.o

commands:
	$(CC) -c $(CMDIR)cat.c -o $(LIBS)cat.o
	$(CC) -c $(CMDIR)cd.c -o $(LIBS)cd.o

install:
	cp -r $(SYS)$(NAME) /$(SYS)
uninstall:
	rm $(SYS)$(NAME)
clean:
	rm $(SYS)$(NAME)
	rm -r $(LIBS)*
