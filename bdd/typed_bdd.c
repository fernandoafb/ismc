#include "typed_bdd.h"
#include "math.h"
#include "stdlib.h"
#include "../libs/buddy-2.4/src/bdd.h"

typed_bdd new_bdd(b)
bdd b;
{
    typed_bdd temp;
    temp.type = TIPO_BDD;
    temp.bdd = (bdd*) b;
    return temp;
}

bdd** int_to_bdd(i)
int i;
{
    bdd** b = (bdd**) malloc(numero_bits);
    int div = i;
    int res = 0;
    int j = 0;
    while (j < numero_bits)
    {
    	res = div % 2;
    	div = div / 2;
    	*(b+j) = (res == 1) ? (bdd*) &bddtrue : (bdd*) &bddfalse;
    	j++;
    }
    return b;
}

typed_bdd new_ibdd(i)
int i;
{
    typed_bdd temp;
    temp.type = TIPO_INTEIRO;
    int maxInt = pow(2,i) - 1;
    // caso seja maior que o limite para inteiros
    if (i > maxInt) i = maxInt;
    temp.ibdd = (bdd**) int_to_bdd(i);
    return temp;
}

int bdd_to_int(b)
bdd** b;
{
	int i = 0;
	int j = 0;
	while (j < numero_bits)
	{
		if (**(b+j) == bddtrue)
		{
			i += pow(2,j);
		}
	}
	return i;
}
