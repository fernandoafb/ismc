#ifndef CHECK_H_
#define CHECK_H_

#include "../libs/buddy-2.4/src/bdd.h"

#include "typed_bdd.h"

typed_bdd check_AX(typed_bdd f);
typed_bdd check_EX(typed_bdd f);
typed_bdd check_AU(typed_bdd f, typed_bdd g);
typed_bdd check_EU(typed_bdd f, typed_bdd g);
typed_bdd check_AG(typed_bdd f);
typed_bdd check_EG(typed_bdd f);
typed_bdd check_AF(typed_bdd f);
typed_bdd check_EF(typed_bdd f);

#endif /* CHECK_H_ */
