#include "../parser/scanner.h"

int main(int argc, char * argsv[]){
	if (argc > 1)
		yyin = fopen(argv[1], "r");
	yyout = fopen("Output.txt", "w");
	yylex();
	return 0;
}
