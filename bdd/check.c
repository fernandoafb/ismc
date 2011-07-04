#include "check.h"

/*
typed_bdd lfp(Tau : PredicateTransformer)
{
	typed_bdd Q = new_bdd(bddfalse);
	typed_bdd Qlinha := Tau(Q);
	while (Q != Qlinha) {
		Q = Qlinha;
		Qlinha = Tau(Qlinha);
	}
	return Q;
}
*/

/*
typed_bdd gfp(Tau: PredicateTransformer)
{
	typed_bdd Q = new_bdd(bddtrue);
    typed_bdd Qlinha = Tau(Q);
	while (Q != Qlinha) {
		Q = Qlinha;
		Qlinha = Tau(Qlinha);
	}
	return(Q);
}
*/

// Explicitando o transformador de predicados Tau
// lfp Z(v) [g(v) OR (f(v) AND check_EX(Z(v)))]
typed_bdd lfp_EfUg(typed_bdd f, typed_bdd g)
{
    typed_bdd Q = new_bdd(bddfalse);
    typed_bdd Qlinha = typed_bdd_or(g, typed_bdd_and(f, check_EX(Q)));

    while (!typed_bdd_equals(Q, Qlinha)) {
        Q = Qlinha;
        Qlinha = typed_bdd_or(g, typed_bdd_and(f, check_EX(Qlinha)));
    }
    return Q;
}

// Explicitando o transformador de predicados Tau
// gfp Z(v) [f(v) AND check_EX(Z(v))]
typed_bdd gfp_EGf(typed_bdd f)
{
    typed_bdd Q = new_bdd(bddtrue);
    typed_bdd Qlinha = typed_bdd_and(f, check_EX(Q));

    while (!typed_bdd_equals(Q, Qlinha)) {
        Q = Qlinha;
        Qlinha = typed_bdd_and(f, check_EX(Qlinha));
    }
    return Q;
}

typed_bdd compute_fair(){
	//fair = EG true
	return check_EG(new_bdd(bddtrue));
}

typed_bdd check_AX(typed_bdd f){
	//AX f = not EX not f
	typed_bdd not_f = typed_bdd_not(f);
	typed_bdd ex = check_EX(not_f);
	return typed_bdd_not(ex);
}
extern bdd transition_relation; // relacao de transição entre v e v'
extern bdd invariant_relation;

typed_bdd check_EX(typed_bdd f){
	//TODO: to implement
	// produto relacional de f(v') e de sua relação de transição N(v,v')
	// o BuDDy tem essa função, bdd_relprod(a,b,var), que faz o produto relacional
	bdd var = invariant_relation; // proxima atribuição v'
	if (f.type == TIPO_BDD)
	{
		return new_bdd(bdd_relprod((bdd)f.bdd,(bdd)transition_relation,(bdd)var)); // f, N(v,v')
	}
	// tratar inteiros
	else if (f.type == TIPO_IBDD)
	{
		//TODO: implementar ex para inteiros
		return new_bdd(bddtrue);
	}
}

typed_bdd check_AU(typed_bdd f, typed_bdd g){
	//A[f U g] = not E[not g U not f and not g] and not EG not g
	typed_bdd eu = check_EU(typed_bdd_not(g), typed_bdd_and(typed_bdd_not(f),typed_bdd_not(g)));
	typed_bdd eg = check_EG(typed_bdd_not(g));
	return typed_bdd_and(typed_bdd_not(eu), typed_bdd_not(eg));
}

typed_bdd check_EU(typed_bdd f, typed_bdd g){
	//TODO: to implement
	// lfp Z(v) [g(v) OR (f(v) AND check_EX(Z(v)))]
	typed_bdd lfp = lfp_EfUg(f, g);
	typed_bdd ex = check_EX(lfp);
	typed_bdd f_and_ex = typed_bdd_and(f,ex);
	return typed_bdd_or(g,f_and_ex);
}

typed_bdd check_AG(typed_bdd f){
	// AG f = not EF not f
	typed_bdd not_f = typed_bdd_not(f);
	typed_bdd ef = check_EF(not_f);
	return typed_bdd_not(ef);
}

typed_bdd check_EG(typed_bdd f){
	//TODO: to implement
	// gfp Z(v) [f(v) AND check_EX(Z(v))]
	typed_bdd gfp = gfp_EGf(f);
	typed_bdd ex = check_EX(gfp);
	return typed_bdd_and(f,ex);
}


typed_bdd check_AF(typed_bdd f){
	// AF f = not EG not f
	typed_bdd not_f = typed_bdd_not(f);
	typed_bdd eg = check_EG(not_f);
	return typed_bdd_not(eg);
}

typed_bdd check_EF(typed_bdd f){
	// EF f = E [true U f]s
	typed_bdd typed_true = new_bdd(bddtrue);
	typed_bdd eu = check_EU(typed_true,f);
	return eu;
}
