#include <stdlib.h>
#include <stdio.h>

#include "parser/grammar.h"
#include "node/node.h"

#include "bdd/ast_to_bdd.h"

// prototype of bison-generated parser function
int yyparse();

int main(int argc, char *argv[]) {
    node_ptr root;
    bdd result;

	if ((argc > 1) && (freopen(argv[1], "r", stdin) == NULL)) {
		printf("%s: O arquivo %s não pode ser aberto.\n", argv[0], argv[1]);

		exit(EXIT_FAILURE);
	}

    init_bdd();

	root = yyparse();
    result = eval_bdd(root);
    
    bdd_printdot(root);
    bdd_done();

    return EXIT_SUCCESS;
}
