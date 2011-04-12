UTIL = ../utils
lex: input.l
	export BISON_PKGDATADIR=../utils/
	$(UTIL)/bison -y -d -v grammar.y
	$(UTIL)/flex input.l

