#ifndef NODE_H
#define NODE_H 

typedef union {
  int inttype;
  struct node *nodetype;
  struct string *strtype;
  struct bdd *bddtype;
} value;

typedef struct node{
  struct node *link;
  short int type,lineno;
  value left,right;
} node_rec,*node_ptr;

node_ptr new_node(),find_node();
void init_node(),free_node();
int sprint_node();
int print_node_atcol();
void print_node();
void fprint_node();
node_ptr subst_node(),map(),key_node();
int list_length(),member();
void free_list();
node_ptr cons(),car(),cdr(),append(),reverse(),list_minus();
node_ptr unify_node();
void dump_tree();
#define NIL ((node_ptr)0)
#define FAILURE_NODE ((node_ptr)(-1))
#define ATOM_MAX_LENGTH 256

#endif
