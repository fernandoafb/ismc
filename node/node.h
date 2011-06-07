#ifndef NODE_H
#define NODE_H 

typedef union {
  int inttype;
  struct node *nodetype;
  struct string *strtype;
  struct typed_bdd *bddtype;
} value;

typedef struct node{
  struct node *link;
  short int type,lineno;
  short int bdd_ith;
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
void symbol_representation();
short int get_bdd_ith();
short int set_bdd_ith(node_ptr, short int);
#define NIL ((node_ptr)0)
#define FAILURE_NODE ((node_ptr)(-1))
#define ATOM_MAX_LENGTH 256

#endif
