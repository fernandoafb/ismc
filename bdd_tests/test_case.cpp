#include <iostream>
#include "bvec.h"

/* EXP's are just numbers
 *
 */
enum NodeType {CASE, EXP, COLON};

struct node {
    NodeType type;
    int value;
    node *left;
    node *right;
};

/* Builds a sample tree for the following SMV code:
 *
 * case
 *   0 : 5;
 *   1 : 10;
 * esac;
 *
 */
node* build_sample_tree() {
    node *zero = new node;
    zero->type = EXP;
    zero->value = 0;

    node *one = new node;
    one->type = EXP;
    one->value = 1;

    node *five = new node;
    five->type = EXP;
    five->value = 5;

    node *ten = new node;
    ten->type = EXP;
    ten->value = 10;

    node *colon1 = new node;
    colon1->type = COLON;
    colon1->left = zero;
    colon1->right = five;

    node *colon2 = new node;
    colon2->type = COLON;
    colon2->left = one;
    colon2->right = ten;

    node *tree2 = new node;
    tree2->type = CASE;
    tree2->left = colon2;
    tree2->right = NULL;

    node *tree1 = new node;
    tree1->type = CASE;
    tree1->left = colon1;
    tree1->right = tree2;

    return tree1;
}

int next = 0;

bdd eval(node *n) {
    bdd r;
    
    if (n == NULL) return bddfalse;

    switch (n->type) {
        case CASE:
        {
            bdd f = eval(n->left->left);
            bdd g = eval(n->left->right);
            bdd h = eval(n->right);
            
            r = bdd_ite(f, g, h);
            
            return r;
        }
        case EXP:
        {
            r = bdd_ithvar(next++);
            
            return r;
        }
    }
}

int main() {
    bdd_init(1000, 100);
    bdd_setvarnum(10);
    
    node *n = build_sample_tree();
    bdd r = eval(n);
    
    bdd_printdot(r);

    bdd_done();
    return 0;
}
