#ifndef TYPED_BDD_H
#define TYPED_BDD_H

#include "../libs/buddy-2.4/src/bdd.h"
#include "math.h"

#define TIPO_IBDD 1
#define TIPO_BDD 2
#define NUM_BITS_ISMC 2
#define MAX_INT_ISMC pow(2,NUM_BITS_ISMC)-1

typedef struct typed_bdd {
  short int type; // pode ser inteiro (TIPO_INTEIRO) ou bdd (TIPO_BDD)
  bdd *bdd; // caso seja bdd
  bdd **ibdd; // caso seja inteiro, cada valor binario do inteiro é um bdd
} typed_bdd;

typed_bdd new_bdd(), new_ibdd();
bdd** int_to_ibdd();
int ibdd_to_int();

#endif
