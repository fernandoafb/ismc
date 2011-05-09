%{
//---------------------------------------Prologue
#include "scanner.h"
#include "../node/node.h"
#include "grammar.h"
#include "symbols.h"

void yyerror(char *s);


%}   

/*Define o tipo de yylval*/
%union {
  node_ptr node;
  int lineno;
}
//---------------------------------------Bison declarations

//define o simbolo inicial da gramática
%start module
%output "grammar.c"
%debug


//Tokens exportados para o processamento do input.l pelo flex
//Obs: a ordem da definição dos tokens não é importante

%left <lineno> TOK_MODULE
%left <lineno> TOK_VAR TOK_SPEC TOK_NAME
%left <lineno> TOK_ASSIGN
%left <lineno> TOK_OF TOK_CONS TOK_SEMI
%left <lineno> TOK_LP TOK_RP TOK_RB TOK_LCB TOK_RCB
%left <lineno> TOK_EQDEF TOK_TWODOTS
%left <lineno> TOK_SELF
%left <lineno> TOK_CASE TOK_ESAC TOK_COLON
%left <lineno> TOK_ARRAY  TOK_BOOLEAN TOK_INTEGER TOK_REAL TOK_WORD

%left <node> TOK_ATOM TOK_FALSEEXP TOK_TRUEEXP
%left <node> TOK_NUMBER TOK_NUMBER_FRAC TOK_NUMBER_REAL TOK_NUMBER_EXP
%left <node> TOK_NUMBER_WORD

%left  <lineno> TOK_COMMA TOK_IMPLIES TOK_IFF TOK_OR TOK_XOR TOK_XNOR TOK_AND TOK_NOT TOK_QUESTIONMARK
%left  <lineno> TOK_EX TOK_AX TOK_EF TOK_AF TOK_EG TOK_AG TOK_EE TOK_AA
%left  <lineno> TOK_SINCE TOK_UNTIL TOK_TRIGGERED TOK_RELEASES

%left  <lineno> TOK_OP_NEXT TOK_OP_GLOBAL TOK_OP_FUTURE
%left  <lineno> TOK_OP_PREC TOK_OP_NOTPRECNOT TOK_OP_HISTORICAL TOK_OP_ONCE
%left  <lineno> TOK_EQUAL TOK_NOTEQUAL TOK_LT TOK_GT TOK_LE TOK_GE
%left  <lineno> TOK_UNION TOK_SETIN TOK_LSHIFT TOK_RSHIFT
%left  <lineno> TOK_MOD TOK_PLUS TOK_MINUS TOK_TIMES TOK_DIVIDE
%left  <lineno> TOK_NEXT TOK_SMALLINIT
%left  <lineno> TOK_LB TOK_DOT TOK_BIT
%left  <lineno> TOK_UNKNOWN

%type <node> number integer subrange subrangetype
%type <node> constant primary_expr case_element_expr case_element_list_expr
%type <node> multiplicative_expr
%type <node> additive_expr shift_expr
%type <node> set_expr set_list_expr relational_expr
%type <node> ctl_expr pure_ctl_expr ctl_and_expr
%type <node> ctl_or_expr ctl_iff_expr ctl_implies_expr
%type <node> and_expr or_expr iff_expr implies_expr basic_expr
%type <node> simple_expression next_expression ctl_expression
%type <node> itype
%type <node> type_value_list type_value
%type <node> module
%type <node> declarations declaration
%type <node> var var_decl var_decl_list
%type <node> assign assign_list one_assign
%type <node> ctlspec
%type <node> _ctlspec 
%type <node> decl_var_id var_id

//---------------------------------------end Bison declarations     
%%
//---------------------------------------Grammar rules
number        : TOK_NUMBER
              | TOK_PLUS TOK_NUMBER { /* $$ = $2; */ }
              ;

integer       : TOK_NUMBER
              | TOK_PLUS TOK_NUMBER { /* $$ = $2; */ }
              ;

subrange      : integer TOK_TWODOTS integer { /* {$$ = new_node(TWODOTS, $1, $3); */ }
              ;

subrangetype  : shift_expr TOK_TWODOTS shift_expr { /* {$$ = new_node(TWODOTS, $1, $3); */ }
              ;

constant     : TOK_FALSEEXP
             | TOK_TRUEEXP
             | number
             ;

primary_expr :
               constant
             | TOK_MINUS primary_expr { /* $$ = new_node(UMINUS, $2, Nil); */  }
             | TOK_ATOM
             | TOK_LP basic_expr TOK_RP { /* $$ = $2; */  }
             | TOK_NOT primary_expr { /* $$ = new_node(NOT, $2, Nil); */  }
             | TOK_NEXT  TOK_LP basic_expr TOK_RP { /* $$ = new_node(NEXT, $3, Nil); */  }
             | TOK_CASE case_element_list_expr TOK_ESAC { /* $$ = $2; */  }
             ;

case_element_list_expr
             : case_element_expr  { /* $$ = new_node(CASE, $1, failure_make("case conditions are not exhaustive", FAILURE_CASE_NOT_EXHAUSTIVE, yylineno)); */ }
             | case_element_expr case_element_list_expr { /* $$ = new_node(CASE, $1, $2); */  }
             ;

case_element_expr
             : basic_expr TOK_COLON basic_expr TOK_SEMI { /* $$ = build_case_colon_node($1, $3, $2); */ }
             ;

/* concatenation_expr foi substituida por primary_expr */

multiplicative_expr :
               primary_expr
             | multiplicative_expr TOK_TIMES primary_expr  { /* $$ = new_node(TIMES, $1, $3); */ }
             | multiplicative_expr TOK_DIVIDE primary_expr { /* $$ = new_node(DIVIDE, $1, $3); */ }
             | multiplicative_expr TOK_MOD primary_expr  { /* $$ = new_node(MOD, $1, $3); */  }
             ;

additive_expr :
               multiplicative_expr
             | additive_expr TOK_PLUS multiplicative_expr { /* $$ = new_node(PLUS, $1, $3); */  }
             | additive_expr TOK_MINUS multiplicative_expr { /* $$ = new_node(MINUS, $1, $3); */  }
             ;

shift_expr :   additive_expr
             | shift_expr TOK_LSHIFT additive_expr { /* $$ = new_node(LSHIFT, $1, $3); */  }
             | shift_expr TOK_RSHIFT additive_expr { /* $$ = new_node(RSHIFT, $1, $3); */  }
             ;

set_expr     : shift_expr
             | subrange
             | TOK_LCB set_list_expr TOK_RCB { /* $$ = $2; */  }
             ;

set_list_expr: basic_expr
             | set_list_expr TOK_COMMA basic_expr { /* $$ = new_node(UNION, $1, $3); */ }
             ;

relational_expr :
               set_expr
             | relational_expr TOK_EQUAL set_expr { /* $$ = new_node(EQUAL, $1, $3); */ }
             | relational_expr TOK_NOTEQUAL set_expr { /* $$ = new_node(NOTEQUAL, $1, $3); */  }
             | relational_expr TOK_LT set_expr  { /* $$ = new_node(LT, $1, $3); */ }
             | relational_expr TOK_GT set_expr  { /* $$ = new_node(GT, $1, $3); */ }
             | relational_expr TOK_LE set_expr  { /* $$ = new_node(LE, $1, $3); */ }
             | relational_expr TOK_GE set_expr  { /* $$ = new_node(GE, $1, $3); */ }
             ;

ctl_expr     : relational_expr
             | pure_ctl_expr
             ;
   
pure_ctl_expr
             : TOK_EX ctl_expr { /* $$ = new_node(EX, $2, Nil); */ }     
             | TOK_AX ctl_expr { /* $$ = new_node(AX, $2, Nil); */ }    
             | TOK_EF ctl_expr { /* $$ = new_node(EF, $2, Nil); */ }   
             | TOK_AF ctl_expr { /* $$ = new_node(AF, $2, Nil); */ }   
             | TOK_EG ctl_expr { /* $$ = new_node(EG, $2, Nil); */ }   
             | TOK_AG ctl_expr { /* $$ = new_node(AG, $2, Nil); */ }   
             | TOK_AA TOK_LB ctl_implies_expr TOK_UNTIL ctl_implies_expr TOK_RB { /* $$ = new_node(AU, $3, $5); */ }   
             | TOK_EE TOK_LB ctl_implies_expr TOK_UNTIL ctl_implies_expr TOK_RB { /* $$ = new_node(EU, $3, $5); */ }
             | TOK_NOT pure_ctl_expr { /* $$ = new_node(NOT, $2, Nil); */ }
             ;
   
ctl_and_expr :
               ctl_expr
             | ctl_and_expr TOK_AND ctl_expr { /* $$ = new_node(AND, $1, $3); */ }
             ;
ctl_or_expr :
               ctl_and_expr
             | ctl_or_expr TOK_OR ctl_and_expr { /* $$ = new_node(OR, $1, $3); */ }    
             | ctl_or_expr TOK_XOR ctl_and_expr { /* $$ = new_node(XOR, $1, $3); */  }   
             | ctl_or_expr TOK_XNOR ctl_and_expr { /* $$ = new_node(XNOR,$1, $3); */ }  
             ;
ctl_iff_expr :
               ctl_or_expr
             | ctl_iff_expr TOK_IFF ctl_or_expr { /* $$ = new_node(IFF, $1, $3); */ }   
             ;

ctl_implies_expr :
               ctl_iff_expr
             | ctl_iff_expr TOK_IMPLIES ctl_implies_expr { /* $$ = new_node(IMPLIES, $1, $3); */ }
             ;

and_expr :     ctl_expr
             | and_expr TOK_AND ctl_expr { /* $$ = new_node(AND, $1, $3); */ }  
             ;

or_expr :
               and_expr
             | or_expr TOK_OR and_expr { /* $$ = new_node(OR,$1, $3); */ }    
             | or_expr TOK_XOR and_expr { /* $$ = new_node(XOR,$1, $3); */ }   
             | or_expr TOK_XNOR and_expr { /* $$ = new_node(XNOR,$1, $3); */ }  
             ;

iff_expr :
               or_expr
             | iff_expr TOK_IFF or_expr { /* $$ = new_node(IFF, $1, $3); */ }   
             ;

implies_expr : iff_expr
             | iff_expr TOK_IMPLIES implies_expr { /* $$ = new_node(IMPLIES, $1, $3); */ }
             ;

basic_expr : implies_expr
           ;

simple_expression : basic_expr { /* if (!isCorrectExp($$, EXP_SIMPLE)) YYABORT; */ }  
                  ;

next_expression   : basic_expr { /* if (!isCorrectExp($$, EXP_NEXT)) YYABORT; */  }  
                  ;

ctl_expression    : basic_expr { /* if (!isCorrectExp($$, EXP_CTL)) YYABORT; */ }  
                  ;

itype         : TOK_BOOLEAN { /* $$ = new_node(BOOLEAN, Nil, Nil); */  } 
              | subrangetype
              | TOK_LCB type_value_list TOK_RCB { /* $$ = new_node(SCALAR, $2, Nil); */ }
              ;

type_value_list : type_value { /* $$ = cons(find_atom($1), Nil); free_node($1); */ } 
                | type_value_list TOK_COMMA type_value { /* $$ = cons(find_atom($3), $1); free_node($3); */ } 
                ;

type_value    : TOK_ATOM
              | integer
              | TOK_FALSEEXP
              | TOK_TRUEEXP
              ;

module       : TOK_MODULE TOK_ATOM declarations {  $$ = new_node(MODULE, NIL, NIL);/*$2, $3);*/  }
             ;

declarations : { /* $$ = Nil; */  }
             | declarations declaration { /* $$ = cons($2, $1); */ } 
             ;
			 
declaration  : var
             | assign
             | ctlspec
             ;

var           : TOK_VAR { /* $$ = new_node(VAR, Nil, Nil); */ } 
              | TOK_VAR var_decl_list { /* $$ = new_node(VAR, $2, Nil); */ } 
              ;

var_decl_list : var_decl { /* $$ = cons($1, Nil); */ }                 
              | var_decl_list var_decl { /* $$ = cons($2, $1); */ }   
              ;
			  
var_decl      : decl_var_id TOK_COLON itype TOK_SEMI { /* $$ = new_node(COLON, $1, $3); */  }  
              ;

assign        : TOK_ASSIGN assign_list { /* $$ = new_node(ASSIGN, $2, Nil); */  } 
              ;
			  
assign_list   : { /* $$ = Nil; */  }
              | assign_list one_assign { /* $$ = new_node(AND, $1, $2); */  }
              ;
			  
one_assign    : var_id TOK_EQDEF simple_expression TOK_SEMI { /* $$ = new_node(EQDEF, $1, $3); */ }
              | TOK_SMALLINIT TOK_LP var_id TOK_RP TOK_EQDEF simple_expression TOK_SEMI { /* $$ = new_node(EQDEF,
                                        new_node(SMALLINIT, $3, Nil), $6); */ }
              | TOK_NEXT TOK_LP var_id TOK_RP TOK_EQDEF next_expression TOK_SEMI { /* $$ = new_node(EQDEF,
                                        new_node(NEXT, $3, Nil),$6); */ }
              ;

_ctlspec      : ctl_expression optsemi { /* $$ = $1; */  }
              ;

ctlspec       : TOK_SPEC _ctlspec { /* $$ = new_node(SPEC, $2, Nil); */ }
              | TOK_SPEC TOK_NAME var_id TOK_EQDEF  _ctlspec { /* $$ = new_node(SPEC, $2, Nil); */ }
              ;

optsemi       : | TOK_SEMI {}
              ;

decl_var_id   : TOK_ATOM
              ;

var_id        : TOK_ATOM
              ;

//---------------------------------------end Grammar rules
%%
//---------------------------------------Epilogue
//int yywrap()
//{
//  return(1);
//}

//void yyerror(char *s)
//{
//	extern char * yytext;
//	fprintf(stderr, "no token \"%s\": %s\n", yytext, s);
//}

//---------------------------------------end Epilogue

