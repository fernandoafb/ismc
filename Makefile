CC = gcc
CFLAGS = -Wall -Werror -LFence
DEBUG = -g
LFLAGS = -Wall -o
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

ismc: parser $(OBJ)
	@cd parser && $(MAKE)
	@echo "parser completo"
	$(CC) $(LFLAGS) ismc $(OBJ)
	@echo "binário completo"

ismc.c: parser/scanner.h

parser:



clean:
	rm -f *.o
