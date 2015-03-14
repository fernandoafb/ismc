# Palavras Reservadas #

MODULE, DEFINE, MDEFINE, CONSTANTS, VAR, IVAR, FROZENVAR,
INIT, TRANS, INVAR, SPEC, CTLSPEC, LTLSPEC, PSLSPEC, COMPUTE,
NAME, INVARSPEC, FAIRNESS, JUSTICE, COMPASSION, ISA, ASSIGN,
CONSTRAINT, SIMPWFF, CTLWFF, LTLWFF, PSLWFF, COMPWFF, IN, MIN,
MAX, MIRROR, PRED, PREDICATES, process, array, of, boolean,
integer, real, word, word1, bool, signed, unsigned, extend,
resize, sizeof, uwconst, swconst, EX, AX, EF, AF, EG, AG, E, F, O, G,
H, X, Y, Z, A, U, S, V, T, BU, EBF, ABF, EBG, ABG, case, esac, mod, next,
init, union, in, xor, xnor, self, TRUE, FALSE, count

# Identiﬁers #

identifier ::
identifier\_first\_character
| identifier identifier\_consecutive\_character

identifier\_first\_character :: one of
ABCDEFGHIJKLMNOPQRSTUVWXYZ
abcdefghijklmnopqrstuvwxyz

identifier\_consecutive\_character ::
identifier\_first\_character
| digit
| one of $ # -

digit :: one of 0 1 2 3 4 5 6 7 8 9

# Integer Numbers #

integer\_number ::
| digit
| integer\_number digit

# Constants #

constant ::
boolean\_constant
| integer\_constant
| symbolic\_constant

boolean\_constant :: one of
FALSE TRUE

integer\_constant :: integer\_number

symbolic\_constant :: identifier

# Basic Expressions #

basic\_expr :: simple\_expr
| next ( basic\_expr ) -- next expression

# Simple Expression #

simple\_expr::constant -- a constant
| identifier -- a variable identifier
| ( basic\_expr )
| ! basic\_expr -- logical/bitwise NOT
| basic\_expr & basic\_expr -- logical/bitwise AND
| basic\_expr | basic\_expr -- logical/bitwise OR
| basic\_expr xor basic\_expr -- logical/bitwise exclusive OR
| basic\_expr xnor basic\_expr -- logical/bitwise NOT xor
| basic\_expr -> basic\_expr -- logical/bitwise implication
| basic\_expr 

&lt;-&gt;

 basic\_expr -- logical/bitwise equivalence
| basic\_expr = basic\_expr -- equality
| basic\_expr != basic\_expr -- inequality
| basic\_expr < basic\_expr -- less than
| basic\_expr > basic\_expr -- greater than
| basic\_expr <= basic\_expr -- less than or equal
| basic\_expr >= basic\_expr -- greater than or equal
| - basic\_expr -- unary minus
| basic\_expr + basic\_expr -- integer addition
| basic\_expr - basic\_expr -- integer subtraction
| basic\_expr **basic\_expr -- integer multiplication
| basic\_expr / basic\_expr -- integer division
| basic\_expr mod basic\_expr -- integer remainder
| basic\_expr >> basic\_expr -- bit shift right
| basic\_expr << basic\_expr -- bit shift left
| case\_expr -- case expression**

# ASSIGN Declaration #

assign\_constraint:: ASSIGN assign\_list

assign\_list::assign ;
| assign\_list assign ;

assign::
identifier := simple\_expr
| init( identifier ):= simple\_expr
| next( identifier ):= basic\_expr

# Case Expression and If-Then-Else Expression #

case\_expr :: case case\_body esac

case\_body ::
basic\_expr : basic\_expr ;
| case\_body basic\_expr : basic\_expr ;

# Type Speciﬁer #

type\_specifier ::
boolean
| { enumeration\_type\_body }
| integer\_number .. integer\_number

(limitar intervalo até 4)

enumeration\_type\_body ::
enumeration\_type\_value
| enumeration\_type\_body , enumeration\_type\_value

enumeration\_type\_value ::
symbolic\_constant
| integer\_number

# State, Input and Frozen Variables #

var\_declaration :: VAR var\_list

var\_list :: identifier : type\_specifier ;
| var\_list identifier : type\_specifier ;

# Programa #

program::module

# Module Declarations #

module :: MODULE main [module\_body](module_body.md)

module\_body ::
module\_element
| module\_body module\_element

module\_element ::
var\_declaration
| assign\_constraint
| ctl\_specification

# CTL Speciﬁcation #

ctl\_specification :: SPEC ctl\_expr ;

ctl\_expr ::
simple\_expr -- a simple boolean expression
| ( ctl\_expr )
| ! ctl\_expr -- logical not
| ctl\_expr & ctl\_expr -- logical and
| ctl\_expr | ctl\_expr -- logical or
| ctl\_expr xor ctl\_expr -- logical exclusive or
| ctl\_expr xnor ctl\_expr -- logical NOT exclusive or
| ctl\_expr -> ctl\_expr -- logical implies
| ctl\_expr 

&lt;-&gt;

 ctl\_expr -- logical equivalence
| EG ctl\_expr -- exists globally
| EX ctl\_expr -- exists next state
| EF ctl\_expr -- exists finally
| AG ctl\_expr -- forall globally
| AX ctl\_expr -- forall next state
| AF ctl\_expr -- forall finally
| E “[“ ctl\_expr U ctl\_expr “]” -- exists until
| A “[“ ctl\_expr U ctl\_expr “]” -- forall until