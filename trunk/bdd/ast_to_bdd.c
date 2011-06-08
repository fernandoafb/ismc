#include "ast_to_bdd.h"
#include "typed_bdd.h"
#include "../libs/buddy-2.4/src/bvec.h"
#include "../libs/buddy-2.4/src/bdd.h"
#include "../node/string.h"
#include <stdlib.h>

#define PRINT_BDD 1

int next_varnum;

int semantic_test(node_ptr n)
{
	int ltype = (bdd) eval_bdd((node_ptr)n->left.nodetype).type;
	int rtype = (bdd) eval_bdd((node_ptr)n->right.nodetype).type;
	return (ltype == rtype && ltype == TIPO_IBDD);
}

typed_bdd result_bdd(int result)
{
    if (result)
    	return new_bdd(bddtrue);
    else
    	return new_bdd(bddfalse);
}

typed_bdd math_expr(node_ptr n, int op)
{
	bdd** l = (bdd**) eval_bdd((node_ptr)n->left.nodetype).ibdd;
	bdd** r = (bdd**) eval_bdd((node_ptr)n->right.nodetype).ibdd;
	int lval = ibdd_to_int(l);
	int rval = ibdd_to_int(r);
	int result;
	typed_bdd math_typed_bdd;
	switch(op)
	{
		case PLUS: result = lval + rval;
				   result = handle_bounds(result);
				   math_typed_bdd = new_ibdd(result);
			       break;
		case MINUS: result = lval - rval;
				    result = handle_bounds(result);
				    math_typed_bdd = new_ibdd(result);
			        break;
		case DIVIDE: result = lval / rval;
		             result = handle_bounds(result);
		             math_typed_bdd = new_ibdd(result);
			         break;
		case MOD: result = lval % rval;
		          result = handle_bounds(result);
		          math_typed_bdd = new_ibdd(result);
			      break;
		case LT: result = lval < rval;
			     math_typed_bdd = result_bdd(result);
			     break;
		case GT: result = lval > rval;
				 math_typed_bdd = result_bdd(result);
		         break;
		case LE: result = lval <= rval;
				 math_typed_bdd = result_bdd(result);
		         break;
		case GE: result = lval >= rval;
				 math_typed_bdd = result_bdd(result);
		         break;
	}
	return math_typed_bdd;
}

int handle_bounds(int v)
{
	// overflow
	if (v > MAX_INT_ISMC) v = MAX_INT_ISMC;
	// underflow
	if (v < 0) v = 0;
	return v;
}

void instantiate_vars(node_ptr l) {
    if (l != NIL){
    	node_ptr n = car(l);
		if(n->type == COLON){
	    	node_ptr atom = car(n);
	    	if(atom->type == ATOM){
	    		char *varname = ((string_ptr)atom->left.strtype)->text;
	    		printf("::instantiate_vars::Atom founded! %s\n", varname);
	    		set_bdd_ith(atom, next_varnum);
	    		next_varnum++;
	    	}
		}else
			printf("::instantiate_vars::Error: %d!\n", l->type);
		instantiate_vars(cdr(l));
    }
}

void eval_reverse(node_ptr l){
	int vlength;
	if(l != NIL){
		eval_reverse(cdr(l));
		node_ptr n = car(l);
		node_ptr e = car(n);
		switch (n->type) {
			case VAR:
				vlength = list_length(e);
				printf("VAR [%d]\n",vlength);
				bdd_init(1000, 100);
				bdd_setvarnum(vlength);
				next_varnum = 0;
				instantiate_vars(e);
				break;

			case ASSIGN:
				printf("ASSIGN\n");
					typed_bdd result;
                    result = eval_bdd(e);
                    if (PRINT_BDD) {
                    	if (result.bdd) {
                    		bdd_printdot((bdd)result.bdd);
                        }
                    }
				break;

			case SPEC:
				printf("SPEC\n");
				break;
			default:
				printf("::eval_reverse::Error: incorrect formation of parse_tree\n");
		}
	}
}

void eval(node_ptr n) {
	//A parse_tree precisa ser invertida ou o eval pode ser convertido para ser recursivo
    if (n->type == MODULE) {
    	eval_reverse(cdr(n));
    	bdd_done();
    }
}

typed_bdd bdd_equals(node_ptr n)
{
	int ltype = (bdd) eval_bdd((node_ptr)n->left.nodetype).type;
	int rtype = (bdd) eval_bdd((node_ptr)n->right.nodetype).type;
	if (ltype == rtype)
	{
		if (ltype == TIPO_BDD)
		{
			bdd l = (bdd) eval_bdd((node_ptr)n->left.nodetype).bdd;
			bdd r = (bdd) eval_bdd((node_ptr)n->right.nodetype).bdd;
			bdd l_equal_r = bdd_apply(l,r,bddop_biimp);
			return new_bdd(l_equal_r);
		}
		else
		{
			bdd** l = (bdd**) eval_bdd((node_ptr)n->left.nodetype).ibdd;
			bdd** r = (bdd**) eval_bdd((node_ptr)n->right.nodetype).ibdd;
			int i = 0;
			int igual = 1;
			for ( ; i < NUM_BITS_ISMC && igual; i++)
			{
				if (**(l+i) != **(r+i))
				{
					igual = 0;
				}
			}
			return (igual) ? new_bdd(bddtrue) : new_bdd(bddfalse);
		}
	}
	// não era pra ter esse else, é um erro semântico
	// por ex, true == 2
	else {
		return new_bdd(bddfalse);
	}
}

typed_bdd eval_bdd(node_ptr n) {

    if (!n) return new_bdd(bddtrue);

    switch (n->type) {
//        case EQDEF:
//		{
//			// atrib
//			eval_bdd((node_ptr)n->left.nodetype); // var
//			eval_bdd((node_ptr)n->right.nodetype); // exp
//			return 0;
//		}
        case SMALLINIT:
		{
			// um init é como se fosse um eqdef
			// soh q com uma validação pra ocorrer somente uma vez
			// é só isso pq o nodo a esquerda é o valor a ser inicializado
			// a atribuição acontece no nodo pai q eh um eqdef
			return eval_bdd((node_ptr)n->left.nodetype);
		}
        //case NEXT: return 0;
        //case ATOM:
        //{
            //string name = n->value.strtype;
            //int varNum = symbolTable[name];
            //return bdd_ithvar(varNum);
//        	/return 0;
        //}
        case AND:
		{
			bdd l = (bdd) eval_bdd((node_ptr)n->left.nodetype).bdd;
			bdd r = (bdd) eval_bdd((node_ptr)n->right.nodetype).bdd;
			bdd l_and_r = bdd_and(l,r);
			return new_bdd(l_and_r);
		}
        case OR:
		{
			bdd l = (bdd) eval_bdd((node_ptr)n->left.nodetype).bdd;
			bdd r = (bdd) eval_bdd((node_ptr)n->right.nodetype).bdd;
			bdd l_or_r = bdd_or(l,r);
			return new_bdd(l_or_r);
		}
        case XOR:
		{
			bdd l = (bdd) eval_bdd((node_ptr)n->left.nodetype).bdd;
			bdd r = (bdd) eval_bdd((node_ptr)n->right.nodetype).bdd;
			bdd l_xor_r = bdd_xor(l,r);
			return new_bdd(l_xor_r);
		}
        case NOT:
        {
        	bdd l = (bdd) eval_bdd((node_ptr)n->left.nodetype).bdd;
        	// not não tem r, porque é unário e r é nulo
        	bdd not_l = bdd_not(l);
        	return new_bdd(not_l);
        }
        case IMPLIES:
		{
			bdd l = (bdd) eval_bdd((node_ptr)n->left.nodetype).bdd;
			bdd r = (bdd) eval_bdd((node_ptr)n->right.nodetype).bdd;
			bdd l_imp_r = bdd_imp(l,r);
			return new_bdd(l_imp_r);
		}
        case IFF:
		{
			// igualdade, equivalence, bi-implicação
			bdd l = (bdd) eval_bdd((node_ptr)n->left.nodetype).bdd;
			bdd r = (bdd) eval_bdd((node_ptr)n->right.nodetype).bdd;
			bdd l_biimp_r = bdd_biimp(l,r);
			return new_bdd(l_biimp_r);
		}
        case EQUAL:
        {
        	return bdd_equals(n);
        }
        case NOTEQUAL:
        {
        	bdd l = (bdd) bdd_equals(n).bdd;
        	bdd not_l = bdd_not(l);
        	return new_bdd(not_l);
        }
        case PLUS:
        {
        	// tratando erros semanticos
        	// 1 + true
        	int semantic_test_passed = semantic_test(n);
        	if (!semantic_test_passed) return new_ibdd(0);
        	return math_expr(n,PLUS);
        }
        case MINUS:
        {
        	// tratando erros semanticos
        	// 1 - true
        	int semantic_test_passed = semantic_test(n);
        	if (!semantic_test_passed) return new_ibdd(0);
        	return math_expr(n,MINUS);
        }
        case DIVIDE:
        {
        	// tratando erros semanticos
        	// 1 / true
        	int semantic_test_passed = semantic_test(n);
        	if (!semantic_test_passed) return new_ibdd(0);
        	return math_expr(n,DIVIDE);
        }
        case MOD:
        {
        	// tratando erros semanticos
        	// 1 % true
        	int semantic_test_passed = semantic_test(n);
        	if (!semantic_test_passed) return new_ibdd(0);
        	return math_expr(n,MOD);
        }
        case LT:
        {
        	// tratando erros semanticos
        	// 1 < true
        	int semantic_test_passed = semantic_test(n);
        	if (!semantic_test_passed) return new_ibdd(0);
        	return math_expr(n,LT);
        }
        case GT:
        {
        	// tratando erros semanticos
        	// 1 < true
        	int semantic_test_passed = semantic_test(n);
        	if (!semantic_test_passed) return new_ibdd(0);
        	return math_expr(n,GT);
        }
        case LE:
        {
        	// tratando erros semanticos
        	// 1 < true
        	int semantic_test_passed = semantic_test(n);
        	if (!semantic_test_passed) return new_ibdd(0);
        	return math_expr(n,LE);
        }
        case GE:
        {
        	// tratando erros semanticos
        	// 1 < true
        	int semantic_test_passed = semantic_test(n);
        	if (!semantic_test_passed) return new_ibdd(0);
        	return math_expr(n,GE);
        }
        case NUMBER:
        {
            int number = n->left.inttype;
            return new_ibdd(number);
        }
        case TRUEEXP:  return new_bdd(bddtrue);
        case FALSEEXP: return new_bdd(bddfalse);
        case CASE:
		{
            bdd f = (bdd) eval_bdd(n->left.nodetype->left.nodetype).bdd;
            bdd g = (bdd) eval_bdd(n->left.nodetype->right.nodetype).bdd;
            bdd h = (bdd) eval_bdd(n->right.nodetype).bdd;
            return new_bdd(bdd_ite(f, g, h));
		}
    }
}
