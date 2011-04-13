/* ----------------------------definitions------------------------------------ */
%{

#include "grammar.h"

%}

%option yylineno
%option outfile="scanner.c" header-file="scanner.h"
%option noreject
%option always-interactive

/* ---------------------------end definitions--------------------------------- */
%%

"MODULE"                {yylval.lineno = yylineno; return(TOK_MODULE);}
"process"               {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_PROCESS*/);}
"DEFINE"                {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_DEFINE*/);}
"MDEFINE"               {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_ARRAY_DEFINE*/);}
"VAR"                   {yylval.lineno = yylineno; return(TOK_VAR);}
"FROZENVAR"             {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_FROZENVAR*/);}
"IVAR"                  {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_IVAR*/);}
"INIT"                  {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_INIT*/);}
"TRANS"                 {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_TRANS*/);}
"INVAR"                 {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_INVAR*/);}
"SPEC"                  {yylval.lineno = yylineno; return(TOK_SPEC);}
"CTLSPEC"               {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_CTLSPEC*/);}
"LTLSPEC"               {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_LTLSPEC*/);}
"PSLSPEC"               {yylval.lineno = yylineno; /*Parser_switch_to_psl();*/ return(TOK_UNKNOWN/*TOK_PSLSPEC*/);}
"COMPUTE"               {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_COMPUTE*/);}
"INVARSPEC"             {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_INVARSPEC*/);}
"NAME"                  {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_NAME*/);}
"CONSTRAINT"            {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_CONSTRAINT*/);}
"CONSTANTS"             {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_CONSTANTS*/);}
"SIMPWFF"               {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_SIMPWFF*/);}
"NEXTWFF"               {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_NEXTWFF*/);}
"CTLWFF"                {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_CTLWFF*/);}
"LTLWFF"                {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_LTLWFF*/);}
"COMPWFF"               {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_COMPWFF*/);}
"COMPID"                {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_COMPID*/);}
"IN"                    {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_INCONTEXT*/);}
"FAIRNESS"              {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_FAIRNESS*/);}
"JUSTICE"               {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_JUSTICE*/);}
"COMPASSION"            {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_COMPASSION*/);}
"ISA"                   {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_ISA*/);}
"ASSIGN"                {yylval.lineno = yylineno; return(TOK_ASSIGN);}

"array"                 {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_ARRAY*/);}
"bool"                  {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_BOOL*/);}
"of"                    {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_OF*/);}
"boolean"               {yylval.lineno = yylineno; return(TOK_BOOLEAN);}
"integer"               {yylval.lineno = yylineno; return(TOK_INTEGER);}
"Integer"               {yylval.lineno = yylineno; return(TOK_INTEGER);}
"real"                  {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_REAL*/);}
"Real"                  {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_REAL*/);}
"word1"                 {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_WORD1*/);}
"word"                  {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_WORD*/);}
"Word"                  {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_WORD*/);}

"signed"                {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_SIGNED*/);}
"unsigned"              {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_UNSIGNED*/);}
"extend"                {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_EXTEND*/);}

"uwconst"               {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_UWCONST*/);}
"swconst"               {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_SWCONST*/);}

"resize"                {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_WRESIZE*/);}
"sizeof"                {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_WSIZEOF*/);}
"toint"                 {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_WTOINT*/);}
"count"                 {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_COUNT*/);}

"READ"                  {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_WAREAD*/);}
"WRITE"                 {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_WAWRITE*/);}

"EX"                    {yylval.lineno = yylineno; return(TOK_EX);}
"AX"                    {yylval.lineno = yylineno; return(TOK_AX);}
"EF"                    {yylval.lineno = yylineno; return(TOK_EF);}
"AF"                    {yylval.lineno = yylineno; return(TOK_AF);}
"EG"                    {yylval.lineno = yylineno; return(TOK_EG);}
"AG"                    {yylval.lineno = yylineno; return(TOK_AG);}
"E"                     {yylval.lineno = yylineno; return(TOK_EE);}
"F"                     {yylval.lineno = yylineno; return(TOK_OP_FUTURE);}
"O"                     {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_OP_ONCE*/);}
"G"                     {yylval.lineno = yylineno; return(TOK_OP_GLOBAL);}
"H"                     {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_OP_HISTORICAL*/);}
"X"                     {yylval.lineno = yylineno; return(TOK_OP_NEXT);}
"Y"                     {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_OP_PREC*/);}
"Z"                     {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_OP_NOTPRECNOT*/);}
"A"                     {yylval.lineno = yylineno; return(TOK_AA);}
"U"                     {yylval.lineno = yylineno; return(TOK_UNTIL);}
"S"                     {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_SINCE*/);}
"V"                     {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_RELEASES*/);}
"T"                     {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_TRIGGERED*/);}
"BU"                    {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_BUNTIL*/);}
"EBF"                   {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_EBF*/);}
"ABF"                   {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_ABF*/);}
"EBG"                   {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_EBG*/);}
"ABG"                   {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_ABG*/);}
"MIN"                   {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_MMIN*/);}
"MAX"                   {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_MMAX*/);}
"("                     {yylval.lineno = yylineno; return(TOK_LP);}
")"                     {yylval.lineno = yylineno; return(TOK_RP);}
"["                     {yylval.lineno = yylineno; return(TOK_LB);}
"]"                     {yylval.lineno = yylineno; return(TOK_RB);}
"{"                     {yylval.lineno = yylineno; return(TOK_LCB);}
"}"                     {yylval.lineno = yylineno; return(TOK_RCB);}
"FALSE"                 {
                                //yylval.node = new_node(FALSEEXP,Nil,Nil);
                                return(TOK_FALSEEXP);
                        }
"TRUE"                  {
                                //yylval.node = new_node(TRUEEXP,Nil,Nil);
                                return(TOK_TRUEEXP);
                        }
"case"                  {yylval.lineno = yylineno; return(TOK_CASE);}
"esac"                  {yylval.lineno = yylineno; return(TOK_ESAC);}
":="                    {yylval.lineno = yylineno; return(TOK_EQDEF);}
"+"                     {yylval.lineno = yylineno; return(TOK_PLUS);}
"-"                     {yylval.lineno = yylineno; return(TOK_MINUS);}
"*"                     {yylval.lineno = yylineno; return(TOK_TIMES);}
"/"                     {yylval.lineno = yylineno; return(TOK_DIVIDE);}
"mod"                   {yylval.lineno = yylineno; return(TOK_MOD);}
"<<"                    {yylval.lineno = yylineno; return(TOK_LSHIFT);}
">>"                    {yylval.lineno = yylineno; return(TOK_RSHIFT);}
"<<<"                   {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_LROTATE*/);}
">>>"                   {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_RROTATE*/);}
"="                     {yylval.lineno = yylineno; return(TOK_EQUAL);}
"!="                    {yylval.lineno = yylineno; return(TOK_NOTEQUAL);}
"<="                    {yylval.lineno = yylineno; return(TOK_LE);}
">="                    {yylval.lineno = yylineno; return(TOK_GE);}
"<"                     {yylval.lineno = yylineno; return(TOK_LT);}
">"                     {yylval.lineno = yylineno; return(TOK_GT);}
"next"                  {yylval.lineno = yylineno; return(TOK_NEXT);}
"init"                  {yylval.lineno = yylineno; return(TOK_SMALLINIT);}
"self"                  {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_SELF*/);}
"union"                 {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_UNION*/);}
"in"                    {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_SETIN*/);}
".."                    {yylval.lineno = yylineno; return(TOK_TWODOTS);}
"."                     {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_DOT*/);}
"->"                    {yylval.lineno = yylineno; return(TOK_IMPLIES);}
"<->"                   {yylval.lineno = yylineno; return(TOK_IFF);}
"|"                     {yylval.lineno = yylineno; return(TOK_OR);}
"&"                     {yylval.lineno = yylineno; return(TOK_AND);}
"xor"                   {yylval.lineno = yylineno; return(TOK_XOR);}
"xnor"                  {yylval.lineno = yylineno; return(TOK_XNOR);}
"!"                     {yylval.lineno = yylineno; return(TOK_NOT);}
"?"                     {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_QUESTIONMARK*/);}
","                     {yylval.lineno = yylineno; return(TOK_COMMA);}
":"                     {yylval.lineno = yylineno; return(TOK_COLON);}
";"                     {yylval.lineno = yylineno; return(TOK_SEMI);}
"::"                    {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_CONCATENATION*/);}


"PRED"                  {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_PRED*/);}
"PREDICATES"            {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_PREDSLIST*/);}
"MIRROR"                {yylval.lineno = yylineno; return(TOK_UNKNOWN/*TOK_MIRROR*/);}

 /* integer number */
[0-9]+           {
                  /* here tmp can be safely cast to int */
                 // yylval.node = new_node(NUMBER, NODE_FROM_INT((int)(tmp)), Nil);
                  return(TOK_NUMBER);
                 }

 /* identifier */
[A-Za-z_][A-Za-z0-9_\$#-]*  {
                  //yylval.node = new_node(ATOM, (node_ptr)find_string(yytext),Nil);
                  return(TOK_ATOM);
                 }
                 

%%
/* ----------------------------user code-------------------------------------- */

/* ----------------------------end user code---------------------------------- */


