anbn: y.tab.c lex.yy.c
	gcc -g lex.yy.c y.tab.c -o anbn

y.tab.c: anbn.y
	yacc -d anbn.y

lex.yy.c: anbn.l
	flex anbn.l

clean: 
	rm -rf lex.yy.c y.tab.c y.tab.h anbn anbn.dSYM
