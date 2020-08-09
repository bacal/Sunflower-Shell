#A Makefile for the Sunflower Shell!
CC=gcc
NAME=sunsh
LIBS=lib/
SOURCE=./src/
SYS=usr/bin/
CMDLIBS=$(LIBS)cat.o $(LIBS)cd.o $(LIBS)show.o
CMDIR = commands/
FLAGS=-O3 -Wall -lm -pedantic -o

all: sunsh.o sunsh_functions.o
	if [ ! -d $(SYS) ]; then mkdir -p $(SYS); fi
	$(CC) $(LIBS)$(NAME).o $(LIBS)$(NAME)_functions.o $(CMDLIBS)   $(FLAGS)  $(SYS)$(NAME)

readline: readline_lib $(NAME).o
	$(CC) $(LIBS)$(NAME).o $(LIBS)$(NAME)_functions.o $(CMDLIBS)  -lreadline $(FLAGS)  $(SYS)$(NAME)

readline_lib: $(SOURCE)$(NAME)_functions.c builtin
	$(CC) -c -D READLINE $(SOURCE)$(NAME)_functions.c $(FLAGS) $(LIBS)$(NAME)_functions.o

$(NAME).o: $(SOURCE)$(NAME).c 
	if [ ! -d $(LIBS) ]; then mkdir $(LIBS); fi
	$(CC) -c $(SOURCE)$(NAME).c $(FLAGS) $(LIBS)$(NAME).o

$(NAME)_functions.o: $(SOURCE)$(NAME)_functions.c builtin
	$(CC) -c $(SOURCE)$(NAME)_functions.c $(FLAGS) $(LIBS)$(NAME)_functions.o

builtin:
	$(CC) -c $(CMDIR)cat.c -o $(LIBS)cat.o
	$(CC) -c $(CMDIR)cd.c -o $(LIBS)cd.o
	$(CC) -c $(CMDIR)show.c -o $(LIBS)show.o

install:
	cp -r $(SYS)$(NAME) /$(SYS)
uninstall:
	rm $(SYS)$(NAME)
clean:
	rm $(SYS)$(NAME)
	rm -r $(LIBS)*
