%{
int i = 0;
int f = 0;
%}

%%
^[0-9]+$ i++;
^[0-9]+\.[0-9]+$ f++;
%%

int yywrap(){return 1;}
int main(int argc,char** argv){
	yyout = fopen("/dev/null","w");
	yylex();
	printf("integers=%d, floats=%d\n",i,f);
	return 0;
}
