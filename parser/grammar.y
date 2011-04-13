%{
//---------------------------------------Prologue
#include "scanner.h"
#include "parser.h"

void yyerror(char *s);

%}   

/*Define o tipo de yylval*/
%union {
  //node_ptr node;
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
number        : TOK_NUMBER { printf("action: number"); }
              | TOK_PLUS TOK_NUMBER { printf("action: number"); }
              ;

integer       : TOK_NUMBER { printf("action: integer"); }
              | TOK_PLUS TOK_NUMBER { printf("action: integer"); }
              ;

subrange      : integer TOK_TWODOTS integer { printf("action: subrange"); }
              ;

subrangetype  : shift_expr TOK_TWODOTS shift_expr { printf("action: subrangetype"); }
              ;

constant     : TOK_FALSEEXP { printf("action: constant"); }
             | TOK_TRUEEXP { printf("action: constant"); }
             | number { printf("action: constant"); }
             ;

primary_expr :
               constant { printf("action: primary_expr"); }
             | TOK_MINUS primary_expr { printf("action: primary_expr");  }
             | TOK_ATOM { printf("action: primary_expr");  }
             | TOK_LP basic_expr TOK_RP { printf("action: primary_expr");  }
             | TOK_NOT primary_expr { printf("action: primary_expr");  }
             | TOK_NEXT  TOK_LP basic_expr TOK_RP { printf("action: primary_expr");  }
             | TOK_CASE case_element_list_expr TOK_ESAC { printf("action: primary_expr");  }
             ;

case_element_list_expr
             : case_element_expr  { printf("action: case_element_list_expr");  }
             | case_element_expr case_element_list_expr { printf("action: case_element_list_expr");  }
             ;

case_element_expr
             : basic_expr TOK_COLON basic_expr TOK_SEMI { printf("action: case_element_expr"); }
             ;

/* concatenation_expr foi substituida por primary_expr */

multiplicative_expr :
               primary_expr { printf("action: multiplicative_expr");  }
             | multiplicative_expr TOK_TIMES primary_expr  { printf("action: multiplicative_expr");  }
             | multiplicative_expr TOK_DIVIDE primary_expr { printf("action: multiplicative_expr");  }
             | multiplicative_expr TOK_MOD primary_expr  { printf("action: multiplicative_expr");  }
             ;

additive_expr :
               multiplicative_expr { printf("action: additive_expr");  }
             | additive_expr TOK_PLUS multiplicative_expr { printf("action: additive_expr");  }
             | additive_expr TOK_MINUS multiplicative_expr { printf("action: additive_expr");  }
             ;

shift_expr :   additive_expr { printf("action: shift_expr");  }
             | shift_expr TOK_LSHIFT additive_expr { printf("action: shift_expr");  }
             | shift_expr TOK_RSHIFT additive_expr { printf("action: shift_expr");  }
             ;

set_expr     : shift_expr { printf("action: set_expr");  }
             | subrange { printf("action: set_expr");  }
             | TOK_LCB set_list_expr TOK_RCB { printf("action: set_expr");  }
             ;

set_list_expr: basic_expr { printf("action: set_list_expr");  }
             | set_list_expr TOK_COMMA basic_expr { printf("action: set_list_expr");  }
             ;

relational_expr :
               set_expr { printf("action: relational_expr");  }
             | relational_expr TOK_EQUAL set_expr { printf("action: relational_expr");  }
             | relational_expr TOK_NOTEQUAL set_expr { printf("action: relational_expr");  }
             | relational_expr TOK_LT set_expr  { printf("action: relational_expr");  }
             | relational_expr TOK_GT set_expr  { printf("action: relational_expr");  }
             | relational_expr TOK_LE set_expr  { printf("action: relational_expr");  }
             | relational_expr TOK_GE set_expr  { printf("action: relational_expr");  }
             ;

ctl_expr     : relational_expr { printf("action: ctl_expr");  }
             | pure_ctl_expr  { printf("action: ctl_expr");  }
             ;
			 
pure_ctl_expr
             : TOK_EX ctl_expr { printf("action: pure_ctl_expr");  }     
             | TOK_AX ctl_expr { printf("action: pure_ctl_expr");  }    
             | TOK_EF ctl_expr { printf("action: pure_ctl_expr");  }   
             | TOK_AF ctl_expr { printf("action: pure_ctl_expr");  }   
             | TOK_EG ctl_expr { printf("action: pure_ctl_expr");  }   
             | TOK_AG ctl_expr { printf("action: pure_ctl_expr");  }   
             | TOK_AA TOK_LB ctl_implies_expr TOK_UNTIL ctl_implies_expr TOK_RB { printf("action: pure_ctl_expr");  }   
             | TOK_EE TOK_LB ctl_implies_expr TOK_UNTIL ctl_implies_expr TOK_RB { printf("action: pure_ctl_expr");  }
             | TOK_NOT pure_ctl_expr { printf("action: pure_ctl_expr");  }
             ;
			 
ctl_and_expr :
               ctl_expr { printf("action: ctl_and_expr");  }
             | ctl_and_expr TOK_AND ctl_expr { printf("action: ctl_and_expr");  } 
             ;
ctl_or_expr :
               ctl_and_expr { printf("action: ctl_or_expr");  }
             | ctl_or_expr TOK_OR ctl_and_expr { printf("action: ctl_or_expr");  }    
             | ctl_or_expr TOK_XOR ctl_and_expr { printf("action: ctl_or_expr");  }   
             | ctl_or_expr TOK_XNOR ctl_and_expr { printf("action: ctl_or_expr");  }  
             ;
ctl_iff_expr :
               ctl_or_expr { printf("action: ctl_iff_expr");  }
             | ctl_iff_expr TOK_IFF ctl_or_expr { printf("action: ctl_iff_expr");  }   
             ;

ctl_implies_expr : 
               ctl_iff_expr { printf("action: ctl_implies_expr");  }
             | ctl_iff_expr TOK_IMPLIES ctl_implies_expr { printf("action: ctl_implies_expr");  } 
             ;

and_expr :     ctl_expr { printf("action: and_expr");  }
             | and_expr TOK_AND ctl_expr { printf("action: and_expr");  }  
             ;

or_expr :
               and_expr { printf("action: or_expr");  }
             | or_expr TOK_OR and_expr { printf("action: or_expr");  }    
             | or_expr TOK_XOR and_expr { printf("action: or_expr");  }   
             | or_expr TOK_XNOR and_expr { printf("action: or_expr");  }  
             ;

iff_expr :
               or_expr { printf("action: iff_expr");  }
             | iff_expr TOK_IFF or_expr { printf("action: iff_expr");  }   
             ;

implies_expr : 
               iff_expr { printf("action: implies_expr");  }
             | iff_expr TOK_IMPLIES implies_expr { printf("action: implies_expr");  } 
             ;

basic_expr :
             implies_expr { printf("action: basic_expr");  }
           ;

simple_expression : basic_expr { printf("action: simple_expression");  }  
                  ;

next_expression   : basic_expr { printf("action: next_expression");  }  
                  ;

ctl_expression    : basic_expr { printf("action: ctl_expression");  }  
                  ;

itype         : TOK_BOOLEAN { printf("action: itype");  } 
              | subrangetype { printf("action: itype");  }
              | TOK_LCB type_value_list TOK_RCB { printf("action: itype");  }
              ;

type_value_list : type_value { printf("action: type_value_list");  } 
                | type_value_list TOK_COMMA type_value { printf("action: type_value_list");  } 
                ;

type_value    : TOK_ATOM { printf("action: type_value");  }
              | integer { printf("action: type_value");  }
              | TOK_FALSEEXP { printf("action: type_value");  }
              | TOK_TRUEEXP { printf("action: type_value");  }
              ;

module       : TOK_MODULE TOK_ATOM declarations { printf("action: module");  }
             ;

declarations : { printf("action: declarations");  }
             | declarations declaration { printf("action: declarations");  } 
             ;
			 
declaration  : var { printf("action: declaration");  }
             | assign { printf("action: declaration");  }
             | ctlspec { printf("action: declaration");  }
             ;

var           : TOK_VAR { printf("action: var");  } 
              | TOK_VAR var_decl_list { printf("action: var");  } 
              ;

var_decl_list : var_decl { printf("action: var_decl_list");  }                 
              | var_decl_list var_decl { printf("action: var_decl_list");  }   
              ;
			  
var_decl      : decl_var_id TOK_COLON itype TOK_SEMI { printf("action: var_decl");  }  
              ;

assign        : TOK_ASSIGN assign_list { printf("action: assign");  } 
              ;
			  
assign_list   : { printf("action: assign_list");  } /*{$$ = Nil;}*/
              | assign_list one_assign { printf("action: assign_list");  }
              ;
			  
one_assign   : var_id TOK_EQDEF simple_expression TOK_SEMI { printf("action: one_assign");  }
              | TOK_SMALLINIT TOK_LP var_id TOK_RP TOK_EQDEF simple_expression TOK_SEMI { printf("action: one_assign");  }
              | TOK_NEXT TOK_LP var_id TOK_RP TOK_EQDEF next_expression TOK_SEMI { printf("action: one_assign");  }
              ;

_ctlspec      : ctl_expression optsemi { printf("action: _ctlspec");  }
;

ctlspec       : TOK_SPEC _ctlspec { printf("action: ctlspec");  }
              | TOK_SPEC TOK_NAME var_id TOK_EQDEF  _ctlspec { printf("action: ctlspec");  }
;

optsemi      : | TOK_SEMI { printf("action: optsemi"); };

decl_var_id   : TOK_ATOM { printf("action: decl_var_id");  }
              ;

var_id        : TOK_ATOM { printf("action: var_id");  }
              ;

//---------------------------------------end Grammar rules
%%
//---------------------------------------Epilogue
int yywrap()
{
  return(1);
}

void yyerror(char *s)
{
	extern char * yytext;
	fprintf(stderr, "no token \"%s\": %s\n", yytext, s);
}

//---------------------------------------end Epilogue

