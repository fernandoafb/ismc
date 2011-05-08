#include "ast_to_bdd.h"
#include "../libs/buddy-2.4/src/bvec.h"
#include "../libs/buddy-2.4/src/bdd.h"

int next_varnum;

void init_bdd() {
    bdd_init(1000, 100);
    bdd_setvarnum(10);
    next_varnum = 0;
} 

bdd eval_bdd(node_ptr n) {
    if (!n) return bddtrue;

    switch (n->type) {
        case ATOM: return 0; // TODO
        case AND: return bdd_and((bdd)n->left.bddtype, (bdd)n->right.bddtype);
        case OR: return bdd_or((bdd)n->left.bddtype, (bdd)n->right.bddtype);
        case XOR: return bdd_xor((bdd)n->left.bddtype, (bdd)n->right.bddtype);
        case NOT: return bdd_not((bdd)n->left.bddtype);
        case IMPLIES: return bdd_imp((bdd)n->left.bddtype, (bdd)n->right.bddtype);
        case IFF: return bdd_biimp((bdd)n->left.bddtype, (bdd)n->right.bddtype);
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
        case NEXT: return 0;
        case TRUEEXP: return bddtrue;
        case FALSEEXP: return bddfalse;
        case CASE:
		{
            bdd f = eval_bdd(n->left.nodetype->left.nodetype);
            bdd g = eval_bdd(n->left.nodetype->right.nodetype);
            bdd h = eval_bdd(n->right.nodetype);
            return bdd_ite(f, g, h);
		}
        //case EXPR: return 0; // TODO
        case VAR:
            // TODO: associar em alguma tabela de símbolos
            return bdd_ithvar(next_varnum++);
    }
    return 0;
}

