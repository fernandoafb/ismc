%{
//---------------------------------------Prologue

%}   
//---------------------------------------Bison declarations

//Tokens exportados para o processamento do input.l pelo flex
//Obs: a ordem da definição dos tokens não é importante

/*%left <lineno> TOK_CONSTRAINT*/
//%left <lineno> TOK_MODULE /*TOK_PROCESS TOK_CONTEXT TOK_EU TOK_AU TOK_EBU TOK_ABU TOK_MINU TOK_MAXU*/
//%left <lineno> TOK_VAR /*TOK_FROZENVAR TOK_IVAR TOK_DEFINE TOK_ARRAY_DEFINE TOK_INIT TOK_TRANS TOK_INVAR*/ TOK_SPEC /*TOK_CTLSPEC TOK_LTLSPEC TOK_COMPUTE TOK_NAME*/
/*%left <lineno> TOK_PSLSPEC*/
/*%left <lineno> TOK_CONSTANTS*/
/*%left <lineno> TOK_INVARSPEC TOK_FAIRNESS TOK_COMPASSION TOK_JUSTICE*/
//%left <lineno> /*TOK_ISA*/ TOK_ASSIGN
//%left <lineno> /*TOK_OF TOK_CONS*/ TOK_SEMI
//%left <lineno> TOK_LP TOK_RP TOK_RB TOK_LCB TOK_RCB
//%left <lineno> TOK_EQDEF TOK_TWODOTS
/*%left <lineno> TOK_SELF*/
//%left <lineno> TOK_CASE TOK_ESAC TOK_COLON
/*%left <lineno> TOK_INCONTEXT TOK_SIMPWFF TOK_NEXTWFF TOK_LTLWFF TOK_LTLPSL TOK_CTLWFF TOK_COMPWFF TOK_COMPID*/
//%left <lineno> /*TOK_ARRAY*/  TOK_BOOLEAN TOK_INTEGER /*TOK_REAL TOK_WORD*/
/*%left <lineno> TOK_BOOL TOK_WORD1*/
/*%left <lineno> TOK_WAREAD TOK_WAWRITE*/
/*%left <lineno> TOK_SIGNED TOK_UNSIGNED TOK_EXTEND TOK_UWCONST TOK_SWCONST TOK_WRESIZE TOK_WSIZEOF TOK_WTOINT TOK_COUNT*/

//%left <node> /*TOK_ATOM*/ TOK_FALSEEXP TOK_TRUEEXP
//%left <node> TOK_NUMBER /*TOK_NUMBER_FRAC TOK_NUMBER_REAL TOK_NUMBER_EXP*/
/*%left <node> TOK_NUMBER_WORD*/

//%left <lineno> TOK_COMMA TOK_IMPLIES TOK_IFF TOK_OR TOK_XOR TOK_XNOR TOK_AND TOK_NOT /*TOK_QUESTIONMARK*/
//%left <lineno> TOK_EX TOK_AX TOK_EF TOK_AF TOK_EG TOK_AG TOK_EE TOK_AA
//%left <lineno> /*TOK_SINCE*/ TOK_UNTIL /*TOK_TRIGGERED TOK_RELEASES*/
/*%left  <lineno> TOK_EBF TOK_EBG TOK_ABF TOK_ABG TOK_BUNTIL TOK_MMIN TOK_MMAX*/
//%left <lineno> TOK_OP_NEXT TOK_OP_GLOBAL TOK_OP_FUTURE
/*%left  <lineno> TOK_OP_PREC TOK_OP_NOTPRECNOT TOK_OP_HISTORICAL TOK_OP_ONCE*/
//%left <lineno> TOK_EQUAL TOK_NOTEQUAL TOK_LT TOK_GT TOK_LE TOK_GE
//%left <lineno> /*TOK_UNION TOK_SETIN*/ TOK_LSHIFT TOK_RSHIFT /*TOK_LROTATE TOK_RROTATE*/
//%left <lineno> TOK_MOD TOK_PLUS TOK_MINUS TOK_TIMES TOK_DIVIDE
//%left <lineno> TOK_NEXT TOK_SMALLINIT /*TOK_CONCATENATION*/
//%left <lineno> TOK_LB /*TOK_DOT TOK_BIT*/
//%left <lineno> TOK_UNKNOWN
//%left <lineno> TOK_ATOM TOK_NAME /*TOK_DOT TOK_SELF*/

/*%nonassoc <lineno> TOK_PRED TOK_PREDSLIST TOK_MIRROR*/
%token NUM

//---------------------------------------end Bison declarations     
%%
//---------------------------------------Grammar rules
input:    /* empty */
             | input line
     ;
     
line:     '\n'
		 | exp '\n'      { printf ("\t%.10g\n", $1); }
	;

exp:      NUM           { $$ = $1;           }
		 | exp exp '+'   { $$ = $1 + $2;      }
		 | exp exp '-'   { $$ = $1 - $2;      }
		 | exp exp '*'   { $$ = $1 * $2;      }
		 | exp exp '/'   { $$ = $1 / $2;      }
		  /* Exponentiation */
		 | exp exp '^'   { $$ = pow ($1, $2); }
		  /* Unary minus    */
		 | exp 'n'       { $$ = -$1;          }
	;

//---------------------------------------end Grammar rules
%%
//---------------------------------------Epilogue
//---------------------------------------end Epilogue

