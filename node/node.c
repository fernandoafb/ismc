/***************************************************************************\
*module: nodemgr                                                            *
*created: 12-18-87 by KLM                                                   *
*uses: smv.h                                                                *
*init: init_node                                                            *
*                                                                           *
*allocate and initialize nodes                                              *
*                                                                           *
*                                                                           *
* Changed to implement bounded until - Sergio Campos - 05/92                *
*                                                                           *
* Changed implementation of bounded for SMV 2.3                             *
*   - steed@iil.intel.com - 07/92                                           *
*                                                                           *
\***************************************************************************/
#include <stdio.h>
#include <string.h>

#include "storage.h"
#include "node.h"
#include "hash.h"
#include "assoc.h"
#include "init.h"
#include "../parser/symbols.h"

extern int option_print_node_length;
extern int option_print_width;

static mgr_ptr node_mgr;
static hash_ptr node_hash;
hash_ptr subst_hash;
#define NODE_HASH_SIZE 16381

static unsigned node_hash_fun(node)
node_ptr node;
{
  return((((unsigned)  node->type)     )  +
	 (((unsigned)  node->left.inttype) << 1)  +
	 (((unsigned) node->right.inttype) << 2));
}

static unsigned node_eq_fun(node1,node2)
node_ptr node1,node2;
{
  return((node1->left.inttype == node2->left.inttype) &&
	 (node1->right.inttype == node2->right.inttype) &&
	 (node1->type == node2->type));
}



/***************************************************************************\
*function: init_node							    *
*									    *
*initialize node manager						    *
\***************************************************************************/
void init_node()
{
  node_mgr = new_mgr(sizeof(struct node));
  node_hash = new_hash(NODE_HASH_SIZE,node_hash_fun,node_eq_fun,node_mgr);
  subst_hash = new_assoc();
}


/***************************************************************************\
*function: new_node							    *
*									    *
*allocates and initializes space for one node				    *
\***************************************************************************/
node_ptr new_node(type,left,right)
int type;
node_ptr left,right;
{
    extern int yylineno;
    node_ptr temp;
    temp = (node_ptr) new_rec (node_mgr);
    temp -> type = type;
    temp -> lineno = yylineno;
    temp -> left.nodetype = left;
    temp -> right.nodetype = right;
    return temp;
}

node_ptr find_node(type,left,right)
int type;
node_ptr left,right;
{
    extern int yylineno;
    node_rec temp;
    //node_ptr *resptr;
    temp.type = type;
    temp.lineno = yylineno;
    temp.left.nodetype = left;
    temp.right.nodetype = right;
    return((node_ptr)insert_hash(node_hash,&temp));
}


node_ptr cons(x,y)
node_ptr x,y;
{
  return(new_node(LIST,x,y));
}

node_ptr car(x)
node_ptr x;
{
/*    if(x->type == NUMBER) */
/*      catastrophe("car: node type is NUMBER"); */
  return(x->left.nodetype);
}

node_ptr cdr(x)
node_ptr x;
{
/*    if(x->type == NUMBER) */
/*      catastrophe("car: node type is NUMBER"); */
  return(x->right.nodetype);
}

int list_length(l)
node_ptr l;
{
  int i;
  for(i=0; l && l->type==LIST; i++) l=cdr(l);
  if(l)catastrophe("list_length: l->type!=LIST");
  return(i);
}

int member(x,l)
node_ptr x,l;
{
  while(l) {
    if(car(l)==x)return(1);
    l = cdr(l);
  }
  return(0);
}

/* Builds a (reverse) list of elements from l1 that are not in l2.
   Preserves the arguments */
node_ptr list_minus(l1,l2)
node_ptr l1,l2;
{
  node_ptr tmp=NIL;
  while(l1) {
    if(!member(car(l1),l2)) tmp = cons(car(l1),tmp);
    l1=cdr(l1);
  }
  return(tmp);
}

node_ptr append(x,y)
node_ptr x,y;
{
  if(x==NIL)return(y);
  x->right.nodetype = append(x->right.nodetype,y);
  return(x);
}

node_ptr map(f,l)
node_ptr (*f)(),l;
{
  node_ptr t;
  if(l == NIL)return(NIL);
  t = (*f)(car(l));
  return(cons(t,map(f,cdr(l))));
}

void walk(f,l)
void (*f)();
node_ptr l;
{
  //node_ptr t;
  if(l == NIL)return;
  (*f)(car(l));
  walk(f,cdr(l));
}


node_ptr reverse(x)
node_ptr x;
{
  node_ptr y=NIL;
  while(x){
    node_ptr z = x->right.nodetype;
    x->right.nodetype = y;
    y = x;
    x = z;
  }
  return(y);
}

node_ptr last(x)
node_ptr x;
{
  if(!x)catastrophe("last: x == NIL");
  if(!cdr(x))return(car(x));
  return(last(cdr(x)));
}


/***************************************************************************\
*function: free_node							    *
*									    *
*free space allocated to a node						    *
\***************************************************************************/
void free_node(a)
node_ptr a;
{
    free_rec(node_mgr,a);
}

void free_list(a)
node_ptr a;
{
  if(a==NIL)return;
  free_list(cdr(a));
  free_node(a);
}

static int my_strncat(s1,s2,size)
char *s1,*s2;
int size;
{
  while(size && *s2){
    if(*s1)
      s1++;
    else{
      *(s1++) = *(s2++);
      *s1 = 0;
    }
    size--;
  }
  return(!*s2);
}


static int sprint_node1(str,size,n,p)
char *str;
int size;
node_ptr n;
int p;
{
  char *op;
  int prio,
      opkind;     /* 0: unary, 1: binary, 2: terciary, 3:quad */
  if(!n)return(1);
  if(n == (node_ptr)(-1))return(my_strncat(str,"*no value*",size));
  switch(n->type){
  case TRUEEXP:
    return(my_strncat(str,"TRUE",size));
  case FALSEEXP:
    return(my_strncat(str,"FALSE",size));
  case ATOM:
    if(!my_strncat(str,(char*)n->left.strtype,size))return(0);
    if(cdr(n)){
      char buf[ATOM_MAX_LENGTH];
      sprintf(buf,"_%p",cdr(n)); //era %d
      return(my_strncat(str,buf,size));
    }
    return(1);
  case NUMBER:
    {
      char buf[ATOM_MAX_LENGTH];
      sprintf(buf,"%p",car(n)); //%d
      return(my_strncat(str,buf,size));
    }
  case DOT:
    if(!n->left.nodetype)return(sprint_node(str,size,n->right.nodetype));
    return(sprint_node(str,size,n->left.nodetype)
	   && my_strncat(str,".",size)
	   && sprint_node(str,size,n->right.nodetype));
  case LIST:
    return(sprint_node(str,size,n->left.nodetype)
	   && (!n->right.nodetype
	       || (my_strncat(str,",",size)
		   && sprint_node(str,size,n->right.nodetype))));
  case ARRAY:
    return(sprint_node(str,size,n->left.nodetype)
	   && my_strncat(str,"[",size)
	   && sprint_node(str,size,n->right.nodetype)
	   && my_strncat(str,"]",size));
  case CASE: return(my_strncat(str,"case ",size)
		    && sprint_node(str,size,n->left.nodetype)
		    && my_strncat(str," 1: ",size)
		    && sprint_node(str,size,n->right.nodetype)
		    && my_strncat(str," esac",size));
  case COLON: return(sprint_node(str,size,n->left.nodetype)
		     && my_strncat(str," : ",size)
		     && sprint_node(str,size,n->right.nodetype)
		     && my_strncat(str,"; ",size));
  case TWODOTS: op = ".."; prio = 3; opkind = 1; break;
  case IMPLIES: op = "->"; prio = 4; opkind = 1; break;
  case IFF: op = "<->"; prio = 4; opkind = 1; break;
  case OR: op = "|"; prio = 5; opkind = 1; break;
  case AND: op = "&"; prio = 6; opkind = 1; break;
  case NOT: op = "!"; prio = 7; opkind = 0; break;
  case EX: op = "EX "; prio = 8; opkind = 0; break;
  case AX: op = "AX "; prio = 8; opkind = 0; break;
  case EF: op = "EF "; prio = 8; opkind = 0; break;
  case AF: op = "AF "; prio = 8; opkind = 0; break;
  case EG: op = "EG "; prio = 8; opkind = 0; break;
  case AG: op = "AG "; prio = 8; opkind = 0; break;
  case EU:
    if(!my_strncat(str,"E",size))return(0);
    op = "U"; prio = 8; p = 9; opkind = 1; break;
  case AU:
    if(!my_strncat(str,"A",size))return(0);
    op = "U"; prio = 8; p = 9; opkind = 1; break;
  case EBU:
    if(!my_strncat(str,"E",size))return(0);
    op = "BU"; prio = 8; p = 9; opkind = 3; break;
  case ABU:
    if(!my_strncat(str,"A",size))return(0);
    op = "BU"; prio = 8; p = 9; opkind = 3; break;
  case EBF: op = "EBF "; prio = 8; opkind = 2; break;
  case ABF: op = "ABF "; prio = 8; opkind = 2; break;
  case EBG: op = "EBG "; prio = 8; opkind = 2; break;
  case ABG: op = "ABG "; prio = 8; opkind = 2; break;
#ifdef TIMING
  case MINU:
    if(!my_strncat(str,"MIN",size))return(0);
    op = ","; prio = 8; p = 9; opkind = 1; break;
  case MAXU:
    if(!my_strncat(str,"MAX",size))return(0);
    op = ","; prio = 8; p = 9; opkind = 1; break;
#endif
  case EQUAL: op = "="; prio = 9; opkind = 1; break;
  case NOTEQUAL: op = "!="; prio = 9; opkind = 1; break;
  case LT:    op = "<"; prio = 9; opkind = 1; break;
  case GT:    op = ">"; prio = 9; opkind = 1; break;
  case LE:    op = "<="; prio = 9; opkind = 1; break;
  case GE:    op = ">="; prio = 9; opkind = 1; break;
  case UNION: op = "union"; prio = 10; opkind = 1; break;
  case SETIN: op = "in"; prio = 11; opkind = 1; break;
  case SETNOTIN: op = "notin"; prio = 11; opkind = 1; break;
  case MOD:   op = "mod"; prio = 12; opkind = 1; break;
  case PLUS:  op = "+"; prio = 13; opkind = 1; break;
  case MINUS: op = "-"; prio = 13; opkind = 1; break;
  case TIMES: op = "*"; prio = 14; opkind = 1; break;
  case DIVIDE: op = "/"; prio = 14; opkind = 1; break;
  case NEXT:
    if(!my_strncat(str,"next",size))return(0);
    op = ""; prio = 0; p = 1; opkind = 0; break;
  case SMALLINIT:
    if(!my_strncat(str,"init",size))return(0);
    op = ""; prio = 0; p = 1; opkind = 0; break;
  default:
    catastrophe("sprint_node1: type = %d",n->type);
  }
  if(prio < p && !my_strncat(str,"(",size))return(0);
  switch(opkind){
  case 0:
    if(!my_strncat(str,op,size))return(0);
    if(!sprint_node1(str,size,n->left.nodetype,prio))return(0);
    break;
  case 1:
    if(!sprint_node1(str,size,n->left.nodetype,prio))return(0);
    if(!my_strncat(str," ",size))return(0);
    if(!my_strncat(str,op,size))return(0);
    if(!my_strncat(str," ",size))return(0);
    if(!sprint_node1(str,size,n->right.nodetype,prio))return(0);
    break;
  case 2:
    /* EF a..b f */
    if(!my_strncat(str,op,size))return(0);                /* EF */
    if(!sprint_node1(str,size,(n->right.nodetype)->left.nodetype,prio))
                                       return(0);         /* a */
    if(!my_strncat(str,"..",size)) return(0);
    if(!sprint_node1(str,size,(n->right.nodetype)->right.nodetype,prio))
                                       return(0);         /* b */
    if(!my_strncat(str," ",size))return(0);
    if(!sprint_node1(str,size,n->left.nodetype,prio))return(0); /* f */
    break;
  case 3:
    /* E[f BU a..b g] */
    if(!sprint_node1(str,size,(n->left.nodetype)->left.nodetype,prio))
                                       return(0);         /* f */
    if(!my_strncat(str," ",size))return(0);
    if(!my_strncat(str,op,size))return(0);                /* BU */
    if(!my_strncat(str," ",size))return(0);
    if(!sprint_node1(str,size,(n->right.nodetype)->left.nodetype,prio))
                                       return(0);         /* a */
    if(!my_strncat(str,"..",size)) return(0);
    if(!sprint_node1(str,size,(n->right.nodetype)->right.nodetype,prio))
                                       return(0);         /* b */
    if(!my_strncat(str," ",size))return(0);
    if(!sprint_node1(str,size,(n->left.nodetype)->right.nodetype,prio))
                                       return(0);         /* g */
    break;
  }
  if(prio < p && !my_strncat(str,")",size))return(0);
  return(1);
}

int sprint_node(str,size,n)
char *str;
int size;
node_ptr n;
{
  return(sprint_node1(str,size,n,0));
}

void print_node(stream,n)
FILE *stream;
node_ptr n;
{
  print_node_atcol(stream,n,0);
}

/* Printing node to a file */

void fprint_list_cb(ff,l)
FILE *ff;
node_ptr l;
{
  fprintf(ff,"{");
  while(l) {
    fprint_node(ff,car(l));
    if(cdr(l)) fprintf(ff,",");
    l=cdr(l);
  }
  fprintf(ff,"}");
}

void fprint_list_rev(ff,l)
FILE *ff;
node_ptr l;
{
  if(l==NIL) return;
  fprint_list_rev(ff,cdr(l));
  if(cdr(l)) fprintf(ff,",");
  fprint_node(ff,car(l));
  l=cdr(l);
}

static void fprint_node1(ff,n,p)
FILE *ff;
node_ptr n;
int p;
{
  char *op;
  int prio,
      opkind;     /* 0: unary, 1: binary, 2: terciary, 3:quad */
  if(!n)return;
  if(n == (node_ptr)(-1)) { fprintf(ff," *no value* "); return;}
  switch(n->type){
  case TRUEEXP:
    fprintf(ff,"TRUE"); return;
  case FALSEEXP:
    fprintf(ff,"FALSE"); return;
  case ATOM:
    fprintf(ff,"%s",(char*)n->left.strtype); return; //não tinha formato
  case NUMBER:
    fprintf(ff,"%p",car(n)); return; //era %d
  case DOT:
    if(!n->left.nodetype) fprint_node(ff,n->right.nodetype);
    else {
      fprint_node(ff,n->left.nodetype);
      fprintf(ff,".");
      fprint_node(ff,n->right.nodetype);
    }
    return;
  case LIST: fprint_list_cb(ff,n); return;
  case ARRAY:
    fprint_node(ff,n->left.nodetype);
    fprintf(ff,"[");
    fprint_node(ff,n->right.nodetype);
    fprintf(ff,"]");
    return;
  case CASE: 
    fprintf(ff,"case ");
    fprint_node(ff,n->left.nodetype);
    fprintf(ff," 1: ");
    fprint_node(ff,n->right.nodetype);
    fprintf(ff," esac");
    return;
  case COLON: 
    fprint_node(ff,n->left.nodetype);
    fprintf(ff," : ");
    fprint_node(ff,n->right.nodetype);
    fprintf(ff,"; ");
    return;
  case HIDE:
  case EXPOSE:
    {
      node_ptr vars=car(n), expr=cdr(n);
      if(n->type==HIDE)fprintf(ff,"hide ");
      else fprintf(ff,"expose ");
      if(!vars)catastrophe("fprint_node: HIDE: vars==NIL");
      fprint_list_rev(ff,vars);
      /* fprint_node(ff,car(vars));vars=cdr(vars);
	 while(vars) {
	 fprintf(ff,",");fprint_node(ff,car(vars)); vars=cdr(vars);
	 } */
      fprintf(ff,": ");
      fprint_node(ff,expr);
      return;
    }
  case TWODOTS: op = ".."; prio = 3; opkind = 1; break;
  case IMPLIES: op = "->"; prio = 4; opkind = 1; break;
  case IFF: op = "<->"; prio = 4; opkind = 1; break;
  case OR: op = "|"; prio = 5; opkind = 1; break;
  case AND: op = "&"; prio = 6; opkind = 1; break;
  case NOT: op = "!"; prio = 7; opkind = 0; break;
  case EX: op = "EX "; prio = 8; opkind = 0; break;
  case AX: op = "AX "; prio = 8; opkind = 0; break;
  case EF: op = "EF "; prio = 8; opkind = 0; break;
  case AF: op = "AF "; prio = 8; opkind = 0; break;
  case EG: op = "EG "; prio = 8; opkind = 0; break;
  case AG: op = "AG "; prio = 8; opkind = 0; break;
  case EU:
    fprintf(ff,"E");
    op = "U"; prio = 8; p = 9; opkind = 1; break;
  case AU:
    fprintf(ff,"A");
    op = "U"; prio = 8; p = 9; opkind = 1; break;
  case EBU:
    fprintf(ff,"E");
    op = "BU"; prio = 8; p = 9; opkind = 3; break;
  case ABU:
    fprintf(ff,"A");
    op = "BU"; prio = 8; p = 9; opkind = 3; break;
  case EBF: op = "EBF "; prio = 8; opkind = 2; break;
  case ABF: op = "ABF "; prio = 8; opkind = 2; break;
  case EBG: op = "EBG "; prio = 8; opkind = 2; break;
  case ABG: op = "ABG "; prio = 8; opkind = 2; break;
#ifdef TIMING
  case MINU:
    fprintf(ff,"MIN");
    op = ","; prio = 8; p = 9; opkind = 1; break;
  case MAXU:
    fprintf(ff,"MAX");
    op = ","; prio = 8; p = 9; opkind = 1; break;
#endif
  case EQUAL: op = "="; prio = 9; opkind = 1; break;
  case NOTEQUAL: op = "!="; prio = 9; opkind = 1; break;
  case LT:    op = "<"; prio = 9; opkind = 1; break;
  case GT:    op = ">"; prio = 9; opkind = 1; break;
  case LE:    op = "<="; prio = 9; opkind = 1; break;
  case GE:    op = ">="; prio = 9; opkind = 1; break;
  case UNION: op = "union"; prio = 10; opkind = 1; break;
  case SETIN: op = "in"; prio = 11; opkind = 1; break;
  case SETNOTIN: op = "notin"; prio = 11; opkind = 1; break;
  case MOD:   op = "mod"; prio = 12; opkind = 1; break;
  case PLUS:  op = "+"; prio = 13; opkind = 1; break;
  case MINUS: op = "-"; prio = 13; opkind = 1; break;
  case TIMES: op = "*"; prio = 14; opkind = 1; break;
  case DIVIDE: op = "/"; prio = 14; opkind = 1; break;
  case NEXT:
    fprintf(ff,"next");
    op = ""; prio = 0; p = 1; opkind = 0; break;
  case SMALLINIT:
    fprintf(ff,"init");
    op = ""; prio = 0; p = 1; opkind = 0; break;
  default:
    catastrophe("fprint_node1: type = %d",n->type);
  }
  if(prio < p)fprintf(ff,"(");
  switch(opkind){
  case 0:
    fprintf(ff,"%s", op);
    fprint_node1(ff,n->left.nodetype,prio);
    break;
  case 1:
    fprint_node1(ff,n->left.nodetype,prio);
    fprintf(ff," %s ",op);
    fprint_node1(ff,n->right.nodetype,prio);
    break;
  case 2:
    /* EF a..b f */
    fprintf(ff,"%s",op);                /* EF */
    fprint_node1(ff,(n->right.nodetype)->left.nodetype,prio); /* a */
    fprintf(ff,"..");
    fprint_node1(ff,(n->right.nodetype)->right.nodetype,prio); /* b */
    fprintf(ff," ");
    fprint_node1(ff,n->left.nodetype,prio); /* f */
    break;
  case 3:
    /* E[f BU a..b g] */
    fprint_node1(ff,(n->left.nodetype)->left.nodetype,prio); /* f */
    fprintf(ff," %s ",op); /* BU */
    fprint_node1(ff,(n->right.nodetype)->left.nodetype,prio); /* a */
    fprintf(ff,"..");
    fprint_node1(ff,(n->right.nodetype)->right.nodetype,prio); /* b */
    fprintf(ff," ");
    fprint_node1(ff,(n->left.nodetype)->right.nodetype,prio); /* g */
    break;
  }
  if(prio < p)fprintf(ff,")");
  return;
}

void fprint_node(ff,n)
FILE *ff;
node_ptr n;
{
  fprint_node1(ff,n,0);
}

void print_node_stdout(n)
node_ptr n;
{
  fprint_node(stdout,n);
}

extern int indent_size;
int print_node_atcol(stream,n,col)
FILE *stream;
node_ptr n;
int col;
{
  char *buf = (char *)stg_malloc(option_print_node_length + 1);
  int c,p;
  if(buf == NULL) rpterr("Out of memory");
  buf[0] = 0;
  c = sprint_node(buf,option_print_node_length,n);
  p = strlen(buf);
  if(!c) p += 3;
  if(col + p >= option_print_width){
    fprintf(stream,"\n");
    col = 0;
    while((col++) < indent_size + 1)fprintf(stream,"  ");
  }
  fprintf(stream,"%s",buf);
  if(!c)fprintf(stream,"...");
  stg_free(buf);
  return(col + p);
}

node_ptr subst_node(n)
node_ptr n;
{
  node_ptr m;
  if(n==NIL)return(n);
  switch(n->type){
  case ATOM:
    m = find_assoc(subst_hash,n);
    if(m)return(m);
    else return(n);
  case ATLINE:
    return(find_node(ATLINE,n->left.nodetype,
		     subst_node(n->right.nodetype)));
  default:
    return(find_node(n->type,
		     subst_node(n->left.nodetype),
		     subst_node(n->right.nodetype)));
  }
}

node_ptr key_node(n)
node_ptr n;
{
  //node_ptr m;
  if(n==NIL)return(n);
  switch(n->type){
  case ATOM:
    {
      char c = *((char*)n->left.strtype);
      if(c <= 'Z' && c >= 'A')return(NIL);
      return(n);
    }
  case ATLINE:
    return(key_node(n->right.nodetype));
  default:
    return(key_node(n->left.nodetype));
  }
}


void make_subst_hash(subst)
node_ptr subst;
{
  clear_hash(subst_hash);
  while(subst){
    node_ptr new = subst->left.nodetype->left.nodetype;
    node_ptr old = subst->left.nodetype->right.nodetype;
    if(find_assoc(subst_hash,old)){
      start_err();
      fprintf(stderr,"Multiple substitution for ");
      print_node(stderr,old);
      finish_err();
    }
    insert_assoc(subst_hash,old,new);
    subst = subst->right.nodetype;
  }
}


int isvar_node(n)
node_ptr n;
{
  char firstchar;
  if(n->type != ATOM)return(0);
  firstchar = *((char*)n->left.strtype);
  return(firstchar <= 'Z' && firstchar >= 'A');
}

static node_ptr subst_list;

static int unify(n1,n2)
node_ptr n1,n2;
{
  int v1,v2;
  node_ptr repl;
  if(n1 == n2)return(1);
  if(n1 == NIL || n2 == NIL)return(0);
  v1 = isvar_node(n1);
  v2 = isvar_node(n2);
  if(v1 && (repl = find_assoc(subst_hash,n1)))
    return(unify(repl,n2));
  if(v2 && (repl = find_assoc(subst_hash,n2)))
    return(unify(n1,repl));
  if(v1){
    insert_assoc(subst_hash,n1,n2);
    subst_list = cons(find_node(OVER,n2,n1),subst_list);
    return(1);
  }
  if(v2){
    insert_assoc(subst_hash,n2,n1);
    subst_list = cons(find_node(OVER,n1,n2),subst_list);
    return(1);
  }
  if(n1->type==ATOM || n2->type==ATOM || n1->type != n2->type)return(0);
  return(unify(car(n1),car(n2)) && unify(cdr(n1),cdr(n2)));
}
  
int occur_check(n)
node_ptr n;
{
  if(n == NIL)return(1);
  if(n->type == OVER)n=cdr(n);
  if(isvar_node(n)){
    node_ptr a = find_assoc(subst_hash,n);
    if(a == FAILURE_NODE)return(0);
    if(n){
      insert_assoc(subst_hash,n,FAILURE_NODE);
      if(!occur_check(a))return(0);
      insert_assoc(subst_hash,n,NIL);
    }
    return(1);
  }
  if(n->type == ATOM)return(1);
  return(occur_check(car(n)) && occur_check(cdr(n)));
}

node_ptr unify_node(n1,n2,sl)
node_ptr n1,n2,sl;
{
  subst_list = sl;
  make_subst_hash(sl);
  if(!unify(n1,n2))return(FAILURE_NODE);
  if(occur_check(subst_list))return(subst_list);
  return(FAILURE_NODE);
}

int match1(n1,n2)
node_ptr n1,n2;
{
  if(n1 == NIL && n2 == NIL)return(1);
  if(n1 == NIL || n2 == NIL)return(0);
  if(isvar_node(n1)){
    node_ptr m = find_assoc(subst_hash,n1);
    if(!m){
      insert_assoc(subst_hash,n1,n2);
      return(1);
    }
    else return(m == n2);
  }
  if(n1->type == ATOM)return(n1 == n2);
  return(n1->type == n2->type
	 && match1(car(n1),car(n2))
	 && match1(cdr(n1),cdr(n2)));
}

int match_node(n1,n2)
node_ptr n1,n2;
{
  clear_hash(subst_hash);
  return(match1(n1,n2));
}

void dump_tree1(node_ptr node, node_ptr pai){
	if(node != NIL && node->type != ATOM && node->type != NUMBER){
		printf("[%p -> %p,%d,%d]\n", pai, node, node->type, node->lineno);
		dump_tree1(node->left.nodetype, node);
		dump_tree1(node->right.nodetype, node);
	}
}

void dump_tree(node_ptr node){
	dump_tree1(node, NIL);
}

void symbol_representation(enum NUSMV_CORE_SYMBOLS type){
	switch (type) {
		case MODULE:
			printf("::symbol_representation::MODULE\n");
			break;
		case VAR:
			printf("::symbol_representation::VAR\n");
			break;
		case ASSIGN:
			printf("::symbol_representation::ASSIGN\n");
			break;
		case SPEC:
			printf("::symbol_representation::SPEC\n");
			break;
		case ATOM:
			printf("::symbol_representation::ATOM\n");
			break;
		case COLON:
			printf("::symbol_representation::COLON\n");
			break;
		case AND:
			printf("::symbol_representation::AND\n");
			break;
		case SMALLINIT:
			printf("::symbol_representation::SMALLINIT\n");
			break;
		case NEXT:
			printf("::symbol_representation::NEXT\n");
			break;
		case EQDEF:
			printf("::symbol_representation::EQDEF\n");
			break;
		default:
			printf("::symbol_representation::Error: symbol not found\n");
			break;
	}

}

/**
 * @return -1 caso o nó não seja ATOM ou o valor do ith
 *
 */
short int get_bdd_ith(node_ptr n){
	if(n->type == ATOM){
		return n->bdd_ith;
	}else
		return -1;
}

/**
 * @return -1 caso o nó não seja ATOM
 */
short int set_bdd_ith(node_ptr n, short int bdd_ith){
	if(n->type == ATOM){
		car(n)->bdd_ith = bdd_ith;
		return 1;
	}else
		return -1;
}
