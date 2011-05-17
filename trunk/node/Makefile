CC = gcc
CFLAGS = -Wall -LFence $(DEBUG) #-Werror
DEBUG = -g
LFLAGS = -Wall -o
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(OBJ)

clean:
	rm -f *.o

