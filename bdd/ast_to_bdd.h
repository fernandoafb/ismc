#ifndef AST_TO_BDD_H
#define AST_TO_BDD_H

#include "../libs/buddy-2.4/src/bdd.h"
#include "../libs/buddy-2.4/src/kernel.h"
#include "../node/node.h"
#include "../parser/symbols.h"
#include "typed_bdd.h"

void init_bdd();
void eval(node_ptr);
typed_bdd eval_bdd(node_ptr);
void instantiate_vars(node_ptr);

typed_bdd bdd_equals(node_ptr);

#endif
