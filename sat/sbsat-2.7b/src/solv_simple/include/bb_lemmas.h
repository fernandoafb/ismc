/* =========FOR INTERNAL USE ONLY. NO DISTRIBUTION PLEASE ========== */

/*********************************************************************
 Copyright 1999-2007, University of Cincinnati.  All rights reserved.
 By using this software the USER indicates that he or she has read,
 understood and will comply with the following:

 --- University of Cincinnati hereby grants USER nonexclusive permission
 to use, copy and/or modify this software for internal, noncommercial,
 research purposes only. Any distribution, including commercial sale
 or license, of this software, copies of the software, its associated
 documentation and/or modifications of either is strictly prohibited
 without the prior consent of University of Cincinnati.  Title to copyright
 to this software and its associated documentation shall at all times
 remain with University of Cincinnati.  Appropriate copyright notice shall
 be placed on all software copies, and a complete copy of this notice
 shall be included in all copies of the associated documentation.
 No right is  granted to use in advertising, publicity or otherwise
 any trademark,  service mark, or the name of University of Cincinnati.


 --- This software and any associated documentation is provided "as is"

 UNIVERSITY OF CINCINNATI MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS
 OR IMPLIED, INCLUDING THOSE OF MERCHANTABILITY OR FITNESS FOR A
 PARTICULAR PURPOSE, OR THAT  USE OF THE SOFTWARE, MODIFICATIONS, OR
 ASSOCIATED DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS,
 TRADEMARKS OR OTHER INTELLECTUAL PROPERTY RIGHTS OF A THIRD PARTY.

 University of Cincinnati shall not be liable under any circumstances for
 any direct, indirect, special, incidental, or consequential damages
 with respect to any claim by USER or any third party on account of
 or arising from the use, or inability to use, this software or its
 associated documentation, even if University of Cincinnati has been advised
 of the possibility of those damages.
*********************************************************************/

#ifndef BB_LEMMAS_S_H
#define BB_LEMMAS_S_H

//Taken from PicoSAT
typedef signed char Val;   /* TRUE, UNDEF, FALSE */
typedef struct Lit Lit;    /* literal */
typedef struct Cls Cls;    /* clause */
struct Lit {
	Val val;
};

struct Cls {
	unsigned size;
	unsigned learned:1;
	unsigned collect:1;
	unsigned connected:1;
	unsigned locked:1;
	unsigned fixed:1;
	unsigned used:1;
/*#ifdef TRACE
	unsigned core:1;
	unsigned collected:1;
#endif*/
//   Cls *uip;
//   Lit *uip_literal;
//   unsigned uip_release_level;
   Cls *next[2];
	Lit *lits[2];
};

//

typedef struct SimpleLemma SimpleLemma;  /* LemmaStruct */

struct SimpleLemma {
	Cls *clause;
	int max_size;
};

extern "C" {
	int  picosat_apply_inference(int var_to_assign, Cls *reason);
	int  picosat_bcp();
	void picosat_set_seed(unsigned random_number_generator_seed);
	void picosat_init_SBSAT(int nNumSmurfs_init);
	void picosat_reset(void);
	void picosat_adjust(int max_idx);
	int  picosat_decide_for_SBSAT(void);
	Lit *int2lit (int l);
}

size_t bytes_clause(unsigned size, unsigned learned);

#endif
