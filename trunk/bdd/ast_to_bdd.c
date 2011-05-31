#include "ast_to_bdd.h"
#include "typed_bdd.h"
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
        typed_bdd result;
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
                    	if (result.bdd) {
                    		//bdd_printdot((bdd)result.bdd);
                        }
                    }
                    break;
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
        case AND: return new_bdd(bdd_and((bdd)eval_bdd((node_ptr)n->left.nodetype).bdd, (bdd)eval_bdd((node_ptr)n->right.nodetype).bdd));
        case OR: return new_bdd(bdd_or((bdd)eval_bdd((node_ptr)n->left.nodetype).bdd, (bdd) eval_bdd((node_ptr)n->right.nodetype).bdd));
        case XOR: return new_bdd(bdd_xor((bdd)eval_bdd((node_ptr)n->left.nodetype).bdd, (bdd)eval_bdd((node_ptr)n->right.nodetype).bdd));
        case NOT: return new_bdd(bdd_not((bdd)eval_bdd((node_ptr)n->left.nodetype).bdd));
        case IMPLIES: return new_bdd(bdd_imp((bdd)eval_bdd((node_ptr)n->left.nodetype).bdd, (bdd)eval_bdd((node_ptr)n->right.nodetype).bdd));
        case IFF: return new_bdd(bdd_biimp((bdd)eval_bdd((node_ptr)n->left.nodetype).bdd, (bdd)eval_bdd((node_ptr)n->right.nodetype).bdd));
        //case EQUAL:
        //case NOTEQUAL:
        //case PLUS:
        //case MINUS:
        //case DIVIDE:
        //case MOD:
        //case LT:
        //case GT:
        //case LE:
        //case GE:
        //case NUMBER:
        //{
            //int num = n->left.inttype;
            //bvec b = num_to_bvec(num);
            //int varNum = symbolTable[name];
            //return bdd_ithvar(varNum);
        	//return 0;
        //}
        case TRUEEXP: return new_bdd(bddtrue);
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

