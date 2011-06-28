#ifndef CHECK_H_
#define CHECK_H_

#include "../libs/buddy-2.4/src/bdd.h"

#include "typed_bdd.h"

typed_bdd rel_prod(typed_bdd f, typed_bdd g, typed_bdd h, typed_bdd E[]);
void cache_insert(typed_bdd f, typed_bdd g, typed_bdd E[], typed_bdd h);
int cached(typed_bdd f, typed_bdd g, typed_bdd E[], typed_bdd h);
int varset_pertence(typed_bdd z, typed_bdd E[]);

typed_bdd check_AX(typed_bdd f);
typed_bdd check_EX(typed_bdd f);
typed_bdd check_AU(typed_bdd f, typed_bdd g);
typed_bdd check_EU(typed_bdd f, typed_bdd g);
typed_bdd check_AG(typed_bdd f);
typed_bdd check_EG(typed_bdd f);
typed_bdd check_AF(typed_bdd f);
typed_bdd check_EF(typed_bdd f);

#endif /* CHECK_H_ */
