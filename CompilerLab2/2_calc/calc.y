%{
void yyerror (char *s);
int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include <ctype.h>
double symbols[52];/*0 to 25 for uppercase letters and 26 to 51 for lowercase letters*/
double symbolVal(char symbol);
void updateSymbolVal(char symbol, double val);
void printNumber(double num);
%}

%error-verbose
%union {double num; char id;}         /* Yacc definitions */
%token print
%token exit_command
%token <num> number
%token <id> identifier
%type <num> line exp term val
%type <id> assignment

/* descriptions of expected inputs     corresponding actions (in C) */
%%
line: assignment ';' {/*printf("Assigned\n")*/;}
    | exit_command ';' {exit(0);}
    | print exp ';' {printNumber($2);}
    | line assignment ';' {/*printf("Assigned\n")*/;}
    | line print exp ';' {printNumber($3);}
    | line exit_command ';' {exit(0);}
    ;

assignment: identifier '=' exp {updateSymbolVal($1,$3);}
	  ;

exp: term {$$ = $1;}
   | exp '+' term {$$ = $1 + $3;}
   | exp '-' term {$$ = $1 - $3;}
   | exp '&' term {$$ = (int)$1 & (int)$3;}
   ;

term: val {$$ = $1;}
    | term '*' val {$$ = $1 * $3;}
    | term '|' val {$$ = (int)$1 | (int)$3;}
    
val: number {$$ = $1;}
   | identifier {$$ = symbolVal($1);} 
   | '-' val {$$ = - $2;}
   ;
%%                     

void printNumber(double num){
	//printf("Printing ");
	int i = (int)num;
	if(i==num)
		printf("%d\n",i);
	else
		printf("%0.2lf\n",num);	
}

int computeSymbolIndex(char token)
{
	int idx = -1;
	if(islower(token)) {
		idx = token - 'a' + 26;
	} else if(isupper(token)) {
		idx = token - 'A';
	}
	return idx;
} 

/* returns the value of a given symbol */
double symbolVal(char symbol)
{
	int bucket = computeSymbolIndex(symbol);
	return symbols[bucket];
}

/* updates the value of a given symbol */
void updateSymbolVal(char symbol, double val)
{
	int bucket = computeSymbolIndex(symbol);
	symbols[bucket] = val;
}

int main (void) {
	/* init symbol table */
	int i;
	for(i=0; i<52; i++) {
		symbols[i] = 0;
	}

	return yyparse ( );
}

void yyerror (char *s) {fprintf (stderr, "%s\n", s);}
