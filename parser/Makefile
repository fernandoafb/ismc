CC = gcc
CFLAGS = -Wall -LFence $(DEBUG)
DEBUG = -g
LFLAGS = -Wall -o
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: bison flex $(OBJ)

bison: grammar.y
	bison -y -d -v grammar.y

grammar.o: ../node/node.h

flex: scanner.l grammar.y
	flex scanner.l

clean:
	rm -f *.o
	rm -f scanner.c scanner.h grammar.c grammar.h
	rm -f grammar.output

