%{
int i;
%}

%%
I i=1;
II i=2;
III i=3;
IV i=4;
V i=5;
VI i=6;
VII i=7;
VIII i=8;
IX i=9;
X i=10;
XI i=11;
XII i=12;
XIII i=13;
XIV i=14;
XV i=15;
XVI i=16;
XVII i=17;
XVIII i=18;
XIX i=19;
XX i=20;
. i=-1;
%%

int yywrap(){return 1;}
int main(){
	yylex();
	if(i==-1)
		printf("Invalid input\n");
	else
		printf("\ndecimal value = %d\n",i);

	return 0;
}
