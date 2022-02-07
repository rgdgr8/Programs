%{
double a[100];
int i = 0;
char e = 'n';
%}

%%
I a[i++]=1;
II a[i++]=2;
III a[i++]=3;
IV a[i++]=4;
V a[i++]=5;
VI a[i++]=6;
VII a[i++]=7;
VIII a[i++]=8;
IX a[i++]=9;
X a[i++]=10;
XI a[i++]=11;
XII a[i++]=12;
XIII a[i++]=13;
XIV a[i++]=14;
XV a[i++]=15;
XVI a[i++]=16;
XVII a[i++]=17;
XVIII a[i++]=18;
XIX a[i++]=19;
XX a[i++]=20;
[+] a[i++]='+';
[-] a[i++]='-';
[*] a[i++]='*';
[/] a[i++]='/';
[ ] e = 'n';
. {e = 'e';printf("error");}
%%

void pr(double *a){	
	printf("i=%d e=%c\n",i,e);
	for(int j=0;j<i;j++)
		printf("%lf ",a[j]);
	printf("\n");
}

int yywrap(){return 1;}
int main(){
	yylex();
	//pr(a);
	if(e=='e' || i<1 || i%2==0)
		printf("Invalid input\n");
	else{
		/*double res = 0;
		if(a[1]=='*')
			res = a[0]*a[2];
		else if(a[1]=='/')
			res = a[0]/a[2];
		else if(a[1]=='+')
			res = a[0]+a[2];
		else if(a[i]=='-')
			res = a[0]-a[2];

		printf("\n%lf\n",res);*/
		double b[100];
		int k = 0;
		for(int j=0;j<i;j++){
			if(a[j]=='*'){
				b[k-1] = b[k-1]*a[j+1];
				j++;
			}
			else if(a[j]=='/'){
				b[k-1] = b[k-1]/a[j+1];
				j++;
			}else{
				b[k++] = a[j];
			}
			//pr(b);
		}
		double res = b[0];
		for(int j=1;j<i;j+=2){
			if(b[j]=='+')
				res += b[j+1];
			else if(b[j]=='-')
				res -= b[j+1];
		}
		
		printf("\n%lf\n",res);
	}

	return 0;
}
