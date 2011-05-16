//#include <map>
#include "ast_to_bdd.h"
#include "../libs/buddy-2.4/src/bvec.h"
#include "../libs/buddy-2.4/src/bdd.h"

int next_varnum;
//std::map<string, int> symbolTable;

void init_bdd() {
    bdd_init(1000, 100);
    bdd_setvarnum(10);
    next_varnum = 0;
} 

bdd eval_bdd(node_ptr n) {
    if (!n) return bddtrue;

    switch (n->type) {
        case MODULE: return eval_bdd(n->right.nodetype);
        case DECLS: return bdd_and(eval_bdd(n->left.nodetype), eval_bdd(n->right.nodetype));
        case VAR:
        {
            //string name = n->value.strtype;
            //symbolTable[name] = next_varnum;
            return bdd_ithvar(next_varnum++);
        }
        case ASSIGN: return eval_bdd(n->left.nodetype);
        case EQDEF: return 0;
        case SMALLINIT: return 0;
        case NEXT: return 0;
        case ATOM:
        {
            //string name = n->value.strtype;
            //int varNum = symbolTable[name];
            //return bdd_ithvar(varNum);
        	return 0;
        }
        case AND: return bdd_and(eval_bdd((node_ptr)n->left.nodetype), eval_bdd((node_ptr)n->right.nodetype));
        case OR: return bdd_or(eval_bdd((node_ptr)n->left.nodetype), eval_bdd((node_ptr)n->right.nodetype));
        case XOR: return bdd_xor(eval_bdd((node_ptr)n->left.nodetype), eval_bdd((node_ptr)n->right.nodetype));
        case NOT: return bdd_not(eval_bdd((node_ptr)n->left.nodetype));
        case IMPLIES: return bdd_imp(eval_bdd((node_ptr)n->left.nodetype), eval_bdd((node_ptr)n->right.nodetype));
        case IFF: return bdd_biimp(eval_bdd((node_ptr)n->left.nodetype), eval_bdd((node_ptr)n->right.nodetype));
        case EQUAL: return 0; // TODO
        case NOTEQUAL: return 0; //TODO
        case PLUS: return 0; // TODO
        case MINUS: return 0;
        case DIVIDE: return 0;
        case MOD: return 0;
        case LT: return 0;
        case GT: return 0;
        case LE: return 0;
        case GE: return 0;
        case NUMBER: return 0;
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
    return 0;
}

