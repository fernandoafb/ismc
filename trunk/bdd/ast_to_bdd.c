#include "ast_to_bdd.h"
#include "../libs/buddy-2.4/src/bvec.h"
#include "../libs/buddy-2.4/src/bdd.h"

#define PRINT_BDD 1

int next_varnum;
//std::map<string, int> symbolTable;

void init_bdd() {
    bdd_init(1000, 100);
    bdd_setvarnum(10);
    next_varnum = 0;
}

// função para testar expressões...
// argumentos devem ser números ou variáveis ou booleanos
// para ser verdadeiro
int test_all_expr(short int a, short int b) {
	return ( (a == NUMBER || a == ATOM || a == TRUEEXP || a == FALSEEXP) &&
			(b == NUMBER || b == ATOM || b == TRUEEXP || b == FALSEEXP) );
}

int test_algebra_expr(short int a, short int b) {
	return ( (a == NUMBER || a == ATOM) &&
			(b == NUMBER || b == ATOM) );
}

void eval(node_ptr n) {
    if (n->type == MODULE) {
        // Avalia as declaracoes, que é uma lista construida com cons()
        node_ptr d = n->right.nodetype;

        while (d) {
            node_ptr e = car(d);
            d = cdr(d);
            
            switch (e->type) {
                case VAR:
                {
                    printf("VAR\n");
                    break;
                }
                case ASSIGN:
                {
                    printf("ASSIGN\n");
                    bdd result = eval_bdd(e);
                    
                    if (PRINT_BDD) {
                        bdd_printdot(result);
                    }
                }
                case SPEC:
                {
                    printf("SPEC\n");
                    break;
                }
            }
        }

        bdd_done();
    }
}

bdd eval_bdd(node_ptr n) {
    if (!n) return bddtrue;

    switch (n->type) {
                //case EQDEF: return 0;
        //case SMALLINIT: return 0;
        //case NEXT: return 0;
        /*case ATOM:
        {
            //string name = n->value.strtype;
            //int varNum = symbolTable[name];
            //return bdd_ithvar(varNum);
        	return 0;
        }
        */
        case AND: return bdd_and(eval_bdd((node_ptr)n->left.nodetype), eval_bdd((node_ptr)n->right.nodetype));
        case OR: return bdd_or(eval_bdd((node_ptr)n->left.nodetype), eval_bdd((node_ptr)n->right.nodetype));
        case XOR: return bdd_xor(eval_bdd((node_ptr)n->left.nodetype), eval_bdd((node_ptr)n->right.nodetype));
        case NOT: return bdd_not(eval_bdd((node_ptr)n->left.nodetype));
        case IMPLIES: return bdd_imp(eval_bdd((node_ptr)n->left.nodetype), eval_bdd((node_ptr)n->right.nodetype));
        case IFF: return bdd_biimp(eval_bdd((node_ptr)n->left.nodetype), eval_bdd((node_ptr)n->right.nodetype));
        case EQUAL:
        {
			if (test_all_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				if (eval_bdd((node_ptr)n->left.nodetype) == eval_bdd((node_ptr)n->right.nodetype))
				{
					return bddtrue;
				}
				else
				{
					return bddfalse;
				}
			}
        }
        case NOTEQUAL:
        {
			if (test_all_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				if (eval_bdd((node_ptr)n->left.nodetype) != eval_bdd((node_ptr)n->right.nodetype))
				{
					return bddtrue;
				}
				else
				{
					return bddfalse;
				}
			}
        }
        case PLUS:
		{
			if (test_algebra_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				int result = eval_bdd((node_ptr)n->left.nodetype) + eval_bdd((node_ptr)n->right.nodetype);
				// TODO terminar
			}
		}
        case MINUS:
		{
			if (test_algebra_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				int result = eval_bdd((node_ptr)n->left.nodetype) - eval_bdd((node_ptr)n->right.nodetype);
				// TODO terminar
			}
		}
        case DIVIDE:
		{
			if (test_algebra_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				int result = eval_bdd((node_ptr)n->left.nodetype) / eval_bdd((node_ptr)n->right.nodetype);
				// TODO terminar
			}
		}
        case MOD:
		{
			if (test_algebra_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				int result = eval_bdd((node_ptr)n->left.nodetype) % eval_bdd((node_ptr)n->right.nodetype);
				// TODO terminar
			}
		}
        case LT:
		{
			if (test_algebra_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				if (eval_bdd((node_ptr)n->left.nodetype) < eval_bdd((node_ptr)n->right.nodetype))
				{
					return bddtrue;
				}
				else
				{
					return bddfalse;
				}
			}
		}
        case GT:
		{
			if (test_algebra_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				if (eval_bdd((node_ptr)n->left.nodetype) > eval_bdd((node_ptr)n->right.nodetype))
				{
					return bddtrue;
				}
				else
				{
					return bddfalse;
				}
			}
		}
        case LE:
        {
			if (test_algebra_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				if (eval_bdd((node_ptr)n->left.nodetype) <= eval_bdd((node_ptr)n->right.nodetype))
				{
					return bddtrue;
				}
				else
				{
					return bddfalse;
				}
			}
        }
        case GE:
        {
			if (test_algebra_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				if (eval_bdd((node_ptr)n->left.nodetype) >= eval_bdd((node_ptr)n->right.nodetype))
				{
					return bddtrue;
				}
				else
				{
					return bddfalse;
				}
			}
        }
        case NUMBER:
        {
            int num = n->left.inttype;
            //int varNum = symbolTable[name];
            //return bdd_ithvar(varNum);
        	//return 0;
        }
        case TRUEEXP: return bddtrue;
        case FALSEEXP: return bddfalse;
        case CASE:
		{
            bdd f = eval_bdd(n->left.nodetype->left.nodetype);
            bdd g = eval_bdd(n->left.nodetype->right.nodetype);
            bdd h = eval_bdd(n->right.nodetype);
            return bdd_ite(f, g, h);
		}
    }
}

