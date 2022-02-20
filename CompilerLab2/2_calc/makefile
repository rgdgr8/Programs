calc: y.tab.c lex.yy.c
	gcc -g lex.yy.c y.tab.c -o calc

y.tab.c: calc.y
	yacc -d calc.y

lex.yy.c: calc.l
	flex calc.l

clean: 
	rm -rf lex.yy.c y.tab.c y.tab.h calc calc.dSYM
