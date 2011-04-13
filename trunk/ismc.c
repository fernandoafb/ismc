#include <stdlib.h>
#include <stdio.h>

#include "parser/parser.h"

// prototype of bison-generated parser function
int yyparse();

int main(int argc, char * argsv[]){
	if ((argc > 1) && (freopen(argsv[1], "r", stdin) == NULL)){
		printf("%s: O arquivo %s não pode ser aberto.", argsv[0], argsv[1]);

		exit( EXIT_FAILURE );
	}

	yyparse();
	return EXIT_SUCCESS;
}
