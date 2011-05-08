CC = gcc
CFLAGS = -Wall -LFence $(LIB) #-Werror 
DEBUG = -g
LFLAGS = -Wall -o
SRC = $(wildcard *.c)
LIB = ../libs/buddy-2.4/src/.libs/libbdd.a
OBJ = $(SRC:.c=.o)

all: $(OBJ)

clean:
	rm -f *.o

