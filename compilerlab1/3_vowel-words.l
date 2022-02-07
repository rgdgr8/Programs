%{
int words = 0;
%}

%%
([ \t\n])+[aeiouAEIOU]([^ \t\n])* words++;
^[aeiouAEIOU][^ \t\n]* words++;
%%

int yywrap(){return 1;}
int main(int argc,char** argv){
	//yyin = fopen("x.txt","r");
	yyout = fopen("/dev/null","w");
	yylex();
	printf("vowel words = %d\n",words);
	return 0;
}
