CC = gcc
CFLAGS = -Wall -Werror -LFence $(LIB)
DEBUG = -g
LFLAGS = -Wall -o
SRC = $(wildcard *.c)
LIB = libs/buddy-2.4/src/.libs/libbdd.a
OBJ = $(SRC:.c=.o) $(wildcard parser/*.o) $(wildcard bdd/*.o) $(wildcard node/*.o)

ismc: submakes $(OBJ)
	$(CC) $(LFLAGS) ismc $(OBJ)
	@echo "binário completo"
	
libs:
	@echo "Construindo bibliotecas"
	@echo "Biblioteca BuDDy"
	@cd libs/buddy-2.4 && $(MAKE)
	@echo "BuDDy completo"
	@echo "Bibliotecas completas"


submakes:	
	@echo "Construindo parser"	
	@cd parser && $(MAKE)
	@echo "parser completo"
	
	@echo "Construindo node"	
	@cd node && $(MAKE)
	@echo "node completo"	
	
	@echo "Construindo bdd"	
	@cd bdd && $(MAKE)
	@echo "bdd completo"	

clean:
	rm -f *.o
