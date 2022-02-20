%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(char* s);
%}

%token A B NL

%%
stmt: S NL {printf("Accepted\n");}
    | stmt S NL {printf("Accepted\n");}
    ;
S: A S B |/* empty string */
 ;
%%

void yyerror(char* s){printf("Rejected\n");exit(1);}
int main(){yyparse(); return 0;}
