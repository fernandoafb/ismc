#include "typed_bdd.h"
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

bdd** int_to_ibdd(i)
int i;
{
    bdd** b = (bdd**) malloc(NUM_BITS_ISMC * sizeof(bdd*));
    int div = i;
    int res = 0;
    int j = 0;
    while (j < NUM_BITS_ISMC)
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
    temp.type = TIPO_IBDD;
    int maxInt = pow(2,i) - 1;
    // caso seja maior que o limite para inteiros
    if (i > maxInt) i = maxInt;
    temp.ibdd = (bdd**) int_to_ibdd(i);
    return temp;
}

typed_bdd new_ibdd_()
{
    typed_bdd temp;
    temp.type = TIPO_IBDD;
    temp.ibdd = (bdd **)malloc(NUM_BITS_ISMC * sizeof(bdd *));
    return temp;
}

int ibdd_to_int(b)
bdd** b;
{
	int i = 0;
	int j = 0;
	while (j < NUM_BITS_ISMC)
	{
		if (**(b+j) == bddtrue)
		{
			i += pow(2,j);
		}
	}
	return i;
}

typed_bdd typed_bdd_biimp(typed_bdd a, typed_bdd b) {
    typed_bdd result;

    if (a.type == TIPO_BDD && b.type == TIPO_BDD) {
        result = new_bdd(bdd_biimp((bdd)a.bdd, (bdd)b.bdd));
    } else if (a.type == TIPO_IBDD && b.type == TIPO_IBDD) {
        int i = 0;
        result = new_ibdd_();
        
        for (i = 0; i < NUM_BITS_ISMC; i++) {
            result.ibdd[i] = (bdd *)bdd_biimp((bdd)a.ibdd[i], (bdd)b.ibdd[i]);
        }
    }

    return result;
}

typed_bdd typed_bdd_imp(typed_bdd a, typed_bdd b) {
    typed_bdd result;

    if (a.type == TIPO_BDD && b.type == TIPO_BDD) {
        result = new_bdd(bdd_imp((bdd)a.bdd, (bdd)b.bdd));
    } else if (a.type == TIPO_IBDD && b.type == TIPO_IBDD) {
        int i = 0;
        result = new_ibdd_();

        for (i = 0; i < NUM_BITS_ISMC; i++) {
            result.ibdd[i] = (bdd *)bdd_imp((bdd)a.ibdd[i], (bdd)b.ibdd[i]);
        }
    }

    return result;
}

typed_bdd typed_bdd_not(typed_bdd a) {
	typed_bdd result;

	if (a.type == TIPO_BDD) {
		result = new_bdd(bdd_not((bdd)a.bdd));
	} else if (a.type == TIPO_IBDD) {
		int i = 0;
		result = new_ibdd_();

		for (i = 0; i < NUM_BITS_ISMC; i++) {
			result.ibdd[i] = (bdd *)bdd_not((bdd)a.ibdd[i]);
		}
	}

	return result;
}

typed_bdd typed_bdd_and(typed_bdd a, typed_bdd b) {
    typed_bdd result;

    if (a.type == TIPO_BDD && b.type == TIPO_BDD) {
        result = new_bdd(bdd_and((bdd)a.bdd, (bdd)b.bdd));
    } else if (a.type == TIPO_IBDD && b.type == TIPO_IBDD) {
        int i = 0;
        result = new_ibdd_();
        
        for (i = 0; i < NUM_BITS_ISMC; i++) {
            result.ibdd[i] = (bdd *)bdd_and((bdd)a.ibdd[i], (bdd)b.ibdd[i]);
        }
    }

    return result;
}

typed_bdd typed_bdd_or(typed_bdd a, typed_bdd b) {
    typed_bdd result;

    if (a.type == TIPO_BDD && b.type == TIPO_BDD) {
        result = new_bdd(bdd_or((bdd)a.bdd, (bdd)b.bdd));
    } else if (a.type == TIPO_IBDD && b.type == TIPO_IBDD) {
        int i = 0;
        result = new_ibdd_();

        for (i = 0; i < NUM_BITS_ISMC; i++) {
            result.ibdd[i] = (bdd *)bdd_or((bdd)a.ibdd[i], (bdd)b.ibdd[i]);
        }
    }

    return result;
}

typed_bdd typed_bdd_xor(typed_bdd a, typed_bdd b) {
    typed_bdd result;

    if (a.type == TIPO_BDD && b.type == TIPO_BDD) {
        result = new_bdd(bdd_xor((bdd)a.bdd, (bdd)b.bdd));
    } else if (a.type == TIPO_IBDD && b.type == TIPO_IBDD) {
        int i = 0;
        result = new_ibdd_();

        for (i = 0; i < NUM_BITS_ISMC; i++) {
            result.ibdd[i] = (bdd *)bdd_xor((bdd)a.ibdd[i], (bdd)b.ibdd[i]);
        }
    }

    return result;
}


int typed_bdd_equals(typed_bdd a, typed_bdd b) {
    int i = 0;
    int igual = 1;
    
    if (a.type == TIPO_BDD && b.type == TIPO_BDD) {
        igual = (a.bdd == b.bdd);
    } else {
        for ( ; i < NUM_BITS_ISMC && igual; i++)
        {
            if ((bdd)a.ibdd[i] != (bdd)b.ibdd[i])
            {
                igual = 0;
            }
        }
    }

    return igual;
}

typed_bdd typed_bdd_ite(typed_bdd a, typed_bdd b, typed_bdd c) {
    typed_bdd result;

    if (a.type == TIPO_BDD && b.type == TIPO_BDD && c.type == TIPO_BDD) {
        result = new_bdd(bdd_ite((bdd)a.bdd, (bdd)b.bdd, (bdd)c.bdd));
    } else if (a.type == TIPO_IBDD && b.type == TIPO_IBDD && c.type == TIPO_IBDD) {
        int i = 0;
        result = new_ibdd_();

        for (i = 0; i < NUM_BITS_ISMC; i++) {
            result.ibdd[i] = (bdd *)bdd_ite((bdd)a.ibdd[i], (bdd)b.ibdd[i], (bdd)c.ibdd[i]);
        }
    }

    return result;
}

