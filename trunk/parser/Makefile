CC = gcc
CFLAGS = -Wall -LFence #-Werror
DEBUG = -g
LFLAGS = -Wall -o
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: bison flex $(OBJ)

bison:
	bison -y -d -v grammar.y

flex:
	flex scanner.l

clean:
	rm -f *.o
	rm -f scanner.c scanner.h grammar.c grammar.h
	rm -f grammar.output

