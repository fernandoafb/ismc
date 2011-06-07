#ifndef TYPED_BDD_H
#define TYPED_BDD_H

#include "../libs/buddy-2.4/src/bdd.h"

#define TIPO_INTEIRO 1
#define TIPO_BDD 2

typedef struct typed_bdd {
  short int type; // pode ser inteiro (TIPO_INTEIRO) ou bdd (TIPO_BDD)
  bdd *bdd; // caso seja bdd
  bdd **inteiro; // caso seja inteiro, cada valor binario do inteiro é um bdd
} typed_bdd;

typed_bdd new_bdd(), new_ibdd();
bdd** int_to_bdd();
int bdd_to_int();

#endif
