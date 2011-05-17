CC = gcc
CFLAGS = -Wall -LFence $(DEBUG)
DEBUG = -g
LFLAGS = -Wall -lm -o
SRC = $(wildcard *.c)
LIB = libs/buddy-2.4/src/.libs/libbdd.a
OBJ = $(SRC:.c=.o) $(wildcard parser/*.o) $(wildcard bdd/*.o) $(wildcard node/*.o) $(LIB)

ismc: submakes $(OBJ)
	$(CC) $(LFLAGS) ismc $(OBJ)
	@echo "binário completo"

buddymake:
	@echo "Construindo bibliotecas"
	@echo "Biblioteca BuDDy"
	@cd libs/buddy-2.4 && ./configure && $(MAKE)
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
	@cd parser && $(MAKE) clean
	@cd node && $(MAKE) clean
	@cd bdd && $(MAKE) clean

