#A Makefile for the B(acal) Shell!

TARGET=bsh
FLAGS="-o"
all:
	gcc $(FLAGS) $(TARGET) $(TARGET).c
clean:
	rm $(TARGET)
