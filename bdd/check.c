#include "check.h"

typed_bdd compute_fair(){
	//fair = EG true
	return check_EG(new_bdd(bddtrue));
}

typed_bdd check_AX(typed_bdd f){
	typed_bdd not_f = typed_bdd_not(f);
	typed_bdd ex = check_EX(not_f);
	return typed_bdd_not(ex);
}

typed_bdd check_EX(typed_bdd f){
	//TODO: to implement
}

typed_bdd check_AU(typed_bdd f, typed_bdd g){
	//A[f U g] = not E[not g U not f and not g] and not EG not g
	typed_bdd eu = check_EU(typed_bdd_not(g), typed_bdd_and(typed_bdd_not(f),typed_bdd_not(g)));
	typed_bdd eg = check_EG(typed_bdd_not(g));
	return typed_bdd_and(typed_bdd_not(eu), typed_bdd_not(eg));
}

typed_bdd check_EU(typed_bdd f, typed_bdd g){
	//TODO: to implement
}

typed_bdd check_AG(typed_bdd f){
	typed_bdd not_f = typed_bdd_not(f);
	typed_bdd ef = check_EF(not_f);
	return typed_bdd_not(ef);
}

typed_bdd check_EG(typed_bdd f){
	//TODO: to implement
}


typed_bdd check_AF(typed_bdd f){
	typed_bdd not_f = typed_bdd_not(f);
	typed_bdd eg = check_EG(not_f);
	return typed_bdd_not(eg);
}

typed_bdd check_EF(typed_bdd f){
	typed_bdd typed_true = new_bdd(bddtrue);
	typed_bdd eu = check_EU(typed_true,f);
	return eu;
}
