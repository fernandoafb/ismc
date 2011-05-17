#include <stdlib.h>
#include <stdio.h>

#include "node/node.h"
#include "parser/grammar.h"

#include "bdd/ast_to_bdd.h"

// prototype of bison-generated parser function
int yyparse();

extern node_ptr parse_tree;

int main(int argc, char *argv[]) {
    node_ptr root;
    bdd result;
    init_storage();
    init_assoc();
    init_node();
	if ((argc > 1) && (freopen(argv[1], "r", stdin) == NULL)) {
		printf("%s: O arquivo %s não pode ser aberto.\n", argv[0], argv[1]);

		exit(EXIT_FAILURE);
	}

    init_bdd();

    yyparse();
    result = eval_bdd(parse_tree);
    
    bdd_printdot(result);
    bdd_done();

    return EXIT_SUCCESS;
}
