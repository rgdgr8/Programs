%{
#include "y.tab.h"
void yyerror(char *s);
%}

%%
"print" {return print;}
"exit" {return exit_command;}
[a-zA-Z] {yylval.id = yytext[0]; return identifier;}//single lettered identifier
[0-9]+\.?[0-9]* {yylval.num = strtod(yytext,NULL); /*printf("Sending %lf\n",yylval.num)*/;return number;}
[&|*+-=;] {/*printf("Sending %c\n",yytext[0])*/;return yytext[0];}
[ \t\n] ;
. {yyerror("Invalid token in lex");}
%%

int yywrap (void) {return 1;}

