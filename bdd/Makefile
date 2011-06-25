CC = gcc
CFLAGS = -Wall -LFence $(DEBUG) #-Werror 
DEBUG = -g
LFLAGS = -Wall -o
SRC = $(wildcard *.c)
LIB = ../libs/buddy-2.4/src/.libs/libbdd.a
OBJ = $(SRC:.c=.o) $(LIB)

all: $(OBJ)

clean:
	rm -f *.o

