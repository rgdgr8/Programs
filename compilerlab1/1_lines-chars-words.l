%{
int lines = 0;
int chars = 0;
int words = 0;
%}

/*rules do cannot properly count words if begginning or end of line is whitespace.*/
%%
[\t ]+ {printf("%s",yytext);words++;}
\n {printf(" = user input line%s",yytext);lines++;words++;}
[^ \t\n] {printf("%s",yytext);chars++;}
%%

int yywrap(){return 1;}
int main(int argc,char** argv){
	//yyin = fopen("x.txt","r");
	yylex();
	printf("lines=%d,characters=%d,words=%d\n",lines,chars,words);
	return 0;
}
