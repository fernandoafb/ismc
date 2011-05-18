#include "ast_to_bdd.h"
#include "../libs/buddy-2.4/src/bvec.h"
#include "../libs/buddy-2.4/src/bdd.h"

#define PRINT_BDD 1

int next_varnum;
//std::map<string, int> symbolTable;

#define INT_DOMAIN 4
#define INT_BIT_SIZE 2

int domain[2] = {INT_DOMAIN,INT_DOMAIN};

void init_bdd() {
    bdd_init(1000, 100);
    bdd_setvarnum(10);
    next_varnum = 0;
}

bvec num_to_bvec(int num)
{
    return bvec_con(INT_BIT_SIZE, num);
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

void instantiate_vars(node_ptr l) {
    if (!l) return;

    instantiate_vars(cdr(l));

    // TODO: associar a variavel car(l) a uma bdd_ithvar()
}

void eval(node_ptr n) {
    if (n->type == MODULE) {
        bdd result;
        node_ptr d = n->right.nodetype;

        // Avalia a lista de declaracoes do módulo
        while (d) {
            node_ptr e = car(d);
            d = cdr(d);
            
            switch (e->type) {
                case VAR:
                {
                    printf("VAR\n");
                    instantiate_vars(e->left.nodetype);

                    break;
                }
                case ASSIGN:
                {
                    printf("ASSIGN\n");
                    result = eval_bdd(e);
                    
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
			    fdd_extdomain(domain, 2);
			    bvec y = bvec_varfdd(1); // eval_bdd((node_ptr)n->left.nodetype); // tratar var e int
			    bvec x = bvec_varfdd(0); // eval_bdd((node_ptr)n->right.nodetype); // tratar var e int
			    bvec z = bvec_add(x,y);
				//return bvec_val(z); // tratar retorno do tipo BVEC pra eval_bdd q retorna bdd
			}
		}
        case MINUS:
		{
			if (test_algebra_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				fdd_extdomain(domain, 2);
				bvec y = bvec_varfdd(1); // eval_bdd((node_ptr)n->left.nodetype); // tratar var e int
				bvec x = bvec_varfdd(0); // eval_bdd((node_ptr)n->right.nodetype); // tratar var e int
				bvec z = bvec_sub(x,y);
				//return bvec_val(z); // tratar retorno do tipo BVEC pra eval_bdd q retorna bdd
			}
		}
        case DIVIDE:
		{
			if (test_algebra_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				fdd_extdomain(domain, 2);
				bvec resto = bvec_varfdd(0);
				bvec resultado = bvec_varfdd(0);
				bvec y = bvec_varfdd(1); // eval_bdd((node_ptr)n->left.nodetype); // tratar var e int
				bvec x = bvec_varfdd(0); // eval_bdd((node_ptr)n->right.nodetype); // tratar var e int
				int resultCode = bvec_div(x,y,&resto,&resultado);
				// bvec_divfixed(x,constante,&resto,&resultado); // caso especial qnd a divisão é por um int
				if (resultCode < 0)
				{
					bvec_free(resto);
					bvec_free(resultado);
				}
				else
				{
					return bvec_val(resultado); // tratar retorno do tipo BVEC pra eval_bdd q retorna bdd
				}
			}
		}
        case MOD:
		{
			// refatorar esse treco, mod e divide sao a msm coisa...
			if (test_algebra_expr(eval_bdd((node_ptr)n->left.nodetype),
					eval_bdd((node_ptr)n->right.nodetype)))
			{
				fdd_extdomain(domain, 2);
				bvec resto = bvec_varfdd(0);
				bvec resultado = bvec_varfdd(0);
				bvec y = bvec_varfdd(1); // eval_bdd((node_ptr)n->left.nodetype); // tratar var e int
				bvec x = bvec_varfdd(0); // eval_bdd((node_ptr)n->right.nodetype); // tratar var e int
				int resultCode = bvec_div(x,y,&resto,&resultado);
				// bvec_divfixed(x,constante,&resto,&resultado); // caso especial qnd a divisão é por um int
				if (resultCode < 0)
				{
					bvec_free(resto);
					bvec_free(resultado);
				}
				else
				{
					return bvec_val(resto); // tratar retorno do tipo BVEC pra eval_bdd q retorna bdd
				}
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
            bvec b = num_to_bvec(num);
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

