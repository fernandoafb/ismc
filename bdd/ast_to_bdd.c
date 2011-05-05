#include "ast_to_bdd.h"
#include "libs/buddy-2.4/src/bvec.h"

int next_varnum;

void init_bdd() {
    bdd_init(1000, 100);
    bdd_setvarnum(10);
    next_varnum = 0;
} 

bdd eval_bdd(node_ptr n) {
    if (!n) return bddtrue;

    switch (n->type) {
        case ATOM: return; // TODO
        case AND: return bdd_and(n->left, n->right);
        case OR: return bdd_or(n->left, n->right);
        case XOR: return bdd_xor(n->left, n->right);
        case NOT: return bdd_not(n->left);
        case IMPLIES: return bdd_imp(n->left, n->right);
        case IFF: return bdd_bimp(n->left, n->right);
        case EQUAL: return; // TODO
        case NOTEQUAL: return; //TODO
        case PLUS: return; // TODO
        case MINUS: return ;
        case DIVIDE: return ;
        case MOD: return ;
        case LT: return ;
        case GT: return ;
        case LE: return ;
        case GE: return ;
        case NUMBER: return ;
        case NEXT: return ;
        case TRUEEXP: return bddtrue;
        case FALSEEXP: return bddfalse;
        case CASE:
            bdd f = eval_bdd(n->left->left);
            bdd g = eval_bdd(n->left->right);
            bdd h = eval_bdd(n->right);
            
            return bdd_ite(f, g, h);
        case EXPR: // TODO
        case VAR:
            // TODO: associar em alguma tabela de símbolos
            return bdd_ithvar(next_varnum++);
    }
}

