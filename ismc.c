#include <stdlib.h>
#include <stdio.h>

#include "node/node.h"
#include "parser/grammar.h"

#include "bdd/ast_to_bdd.h"

// prototype of bison-generated parser function
int yyparse();

extern node_ptr parse_tree;

int main(int argc, char *argv[]) {
    init_node();
	if ((argc > 1) && (freopen(argv[1], "r", stdin) == NULL)) {
		printf("%s: O arquivo %s não pode ser aberto.\n", argv[0], argv[1]);

		exit(EXIT_FAILURE);
	}

    init_bdd();

    yyparse();
    //dump_tree(parse_tree);
    eval(parse_tree);
    //bdd_printall();
    return EXIT_SUCCESS;
}
