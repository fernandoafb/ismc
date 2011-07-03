#include "check.h"

// implementar cache de resultados
// esse vetor de typed_bdd é placeholder
int cached(typed_bdd f, typed_bdd g, typed_bdd E[], typed_bdd h)
{
	//TODO: to implement
	return 0;
}

void cache_insert(typed_bdd f, typed_bdd g, typed_bdd E[], typed_bdd h)
{
	//TODO: to implement
}

int varset_pertence(typed_bdd z, typed_bdd E[])
{
	//TODO: to implement
	return 0;
}

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

// arcabouço básico... ainda está longe de pronto
// esse vetor de typed_bdd é placeholder
typed_bdd rel_prod(typed_bdd f, typed_bdd g, typed_bdd h, typed_bdd E[])
{
	if (typed_bdd_equals(f,new_bdd(bddfalse)) || typed_bdd_equals(g,new_bdd(bddfalse)))
	{
		return new_bdd(bddfalse);
	}
	else if (typed_bdd_equals(f,new_bdd(bddtrue)) && typed_bdd_equals(g,new_bdd(bddtrue)))
	{
		return new_bdd(bddtrue);
	}
	else if (cached(f,g,E,h))
	{
		return h;
	}
	else
	{
		// let x be the top variable of f
		// let y be the top variable of g
		// let z be the topmost of x and y
		typed_bdd z;
		typed_bdd h0 = rel_prod(f,g,h,E); // nesse f e g, fazer z valer 0
		typed_bdd h1 = rel_prod(f,g,h,E); // nesse f e g, fazer z valer 1
		if (varset_pertence(z,E))
		{
			h = typed_bdd_or(h0,h1); /* h0 OR h1 */
		}
		else
		{
			h = typed_bdd_ite(z,h1,h0); /* (z AND h1) OR (not z AND h0) */
		}
		cache_insert(f,g,E,h);
		return h;
	}
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
