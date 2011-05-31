#include "typed_bdd.h"
#include "../libs/buddy-2.4/src/bdd.h"

typed_bdd new_bdd(b)
bdd b;
{
    typed_bdd temp;
    temp.type = TIPO_BDD;
    temp.bdd = (bdd*) b;
    return temp;
}

typed_bdd new_inteiro(b)
bdd b[];
{
    typed_bdd temp;
    temp.type = TIPO_INTEIRO;
    temp.inteiro = (bdd**) b;
    return temp;
}

bdd int_to_bdd(i)
int i;
{
	return 0;
}

int bdd_to_int(b)
bdd b;
{
	return 0;
}
