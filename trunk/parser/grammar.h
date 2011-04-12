
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_MODULE = 258,
     TOK_SPEC = 259,
     TOK_VAR = 260,
     TOK_ASSIGN = 261,
     TOK_SEMI = 262,
     TOK_RCB = 263,
     TOK_LCB = 264,
     TOK_RB = 265,
     TOK_RP = 266,
     TOK_LP = 267,
     TOK_TWODOTS = 268,
     TOK_EQDEF = 269,
     TOK_COLON = 270,
     TOK_ESAC = 271,
     TOK_CASE = 272,
     TOK_INTEGER = 273,
     TOK_BOOLEAN = 274,
     TOK_TRUEEXP = 275,
     TOK_FALSEEXP = 276,
     TOK_NUMBER = 277,
     TOK_NOT = 278,
     TOK_AND = 279,
     TOK_XNOR = 280,
     TOK_XOR = 281,
     TOK_OR = 282,
     TOK_IFF = 283,
     TOK_IMPLIES = 284,
     TOK_COMMA = 285,
     TOK_AA = 286,
     TOK_EE = 287,
     TOK_AG = 288,
     TOK_EG = 289,
     TOK_AF = 290,
     TOK_EF = 291,
     TOK_AX = 292,
     TOK_EX = 293,
     TOK_UNTIL = 294,
     TOK_OP_FUTURE = 295,
     TOK_OP_GLOBAL = 296,
     TOK_OP_NEXT = 297,
     TOK_GE = 298,
     TOK_LE = 299,
     TOK_GT = 300,
     TOK_LT = 301,
     TOK_NOTEQUAL = 302,
     TOK_EQUAL = 303,
     TOK_RSHIFT = 304,
     TOK_LSHIFT = 305,
     TOK_DIVIDE = 306,
     TOK_TIMES = 307,
     TOK_MINUS = 308,
     TOK_PLUS = 309,
     TOK_MOD = 310,
     TOK_SMALLINIT = 311,
     TOK_NEXT = 312,
     TOK_LB = 313,
     TOK_UNKNOWN = 314,
     TOK_NAME = 315,
     TOK_ATOM = 316
   };
#endif
/* Tokens.  */
#define TOK_MODULE 258
#define TOK_SPEC 259
#define TOK_VAR 260
#define TOK_ASSIGN 261
#define TOK_SEMI 262
#define TOK_RCB 263
#define TOK_LCB 264
#define TOK_RB 265
#define TOK_RP 266
#define TOK_LP 267
#define TOK_TWODOTS 268
#define TOK_EQDEF 269
#define TOK_COLON 270
#define TOK_ESAC 271
#define TOK_CASE 272
#define TOK_INTEGER 273
#define TOK_BOOLEAN 274
#define TOK_TRUEEXP 275
#define TOK_FALSEEXP 276
#define TOK_NUMBER 277
#define TOK_NOT 278
#define TOK_AND 279
#define TOK_XNOR 280
#define TOK_XOR 281
#define TOK_OR 282
#define TOK_IFF 283
#define TOK_IMPLIES 284
#define TOK_COMMA 285
#define TOK_AA 286
#define TOK_EE 287
#define TOK_AG 288
#define TOK_EG 289
#define TOK_AF 290
#define TOK_EF 291
#define TOK_AX 292
#define TOK_EX 293
#define TOK_UNTIL 294
#define TOK_OP_FUTURE 295
#define TOK_OP_GLOBAL 296
#define TOK_OP_NEXT 297
#define TOK_GE 298
#define TOK_LE 299
#define TOK_GT 300
#define TOK_LT 301
#define TOK_NOTEQUAL 302
#define TOK_EQUAL 303
#define TOK_RSHIFT 304
#define TOK_LSHIFT 305
#define TOK_DIVIDE 306
#define TOK_TIMES 307
#define TOK_MINUS 308
#define TOK_PLUS 309
#define TOK_MOD 310
#define TOK_SMALLINIT 311
#define TOK_NEXT 312
#define TOK_LB 313
#define TOK_UNKNOWN 314
#define TOK_NAME 315
#define TOK_ATOM 316




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 7 "grammar.y"

  //node_ptr node;
  int lineno;



/* Line 1676 of yacc.c  */
#line 181 "grammar.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


