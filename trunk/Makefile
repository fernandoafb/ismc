CC = gcc
CFLAGS = -Wall -Werror -LFence
DEBUG = -g
LFLAGS = -Wall -o
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o) $(wildcard parser/*.o)

ismc: submakes $(OBJ)
	$(CC) $(LFLAGS) ismc $(OBJ)
	@echo "binário completo"

submakes:
	@echo "Construindo parser"	
	@cd parser && $(MAKE)
	@echo "parser completo"

clean:
	rm -f *.o
