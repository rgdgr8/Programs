#include <stdlib.h>
#include <iostream>
#include <cctype>
using namespace std;
/*
 
 * Grammar for accepting algebraic expression(for addition and multiplication)
 * and/or identifier names starting with an english letter (without whitespaces)
 	
 	E –> E + T | T 
	T –> T * F | F 
	F –> ( E ) | id

 * Same Grammar after left recursion removal
 
	E->TE'
	E'->+TE'|e
	T->FT'
	T'->*FT'|e
	F->id|const|(E)

*/

char *ch;
int err;
void E();
void E_();
void T();
void T_();
void F();

void E()
{
	T();
	E_();
	cout<<"E->TE'"<<endl;
}
void E_()
{
	cout<<"E'->";
	if (*ch == '+')
	{
		ch++;
		T();
		E_();
		cout<<"TE'\n";
	}
	else
		cout<<"e'\n'";
		return;
}
void T()
{
	F();
	T_();
	cout<<"T->FT'\n";
}
void T_()
{
	cout<<"T'->";
	if (*ch == '*')
	{
		ch++;
		F();
		T_();
		cout<<"*FT'\n";
	}
	else
		cout<<"e\n";
		return;
}
void F()
{
	cout<<"F->";
	if (isalpha(*ch))
	{
		while (isalnum(*ch) || *ch == '_')
			ch++;
		cout<<"id\n";
	}
	else if (isdigit(*ch))
	{
		while (isdigit(*ch))
			ch++;
		cout<<"const\n";
	}
	else if (*ch == '(')
	{
		ch++;
		E();
		if (*ch == ')')
			ch++;
		cout<<"(E)\n";
		else
			err = 1;
	}
	else
		err = 1;
}

int main()
{
	char buffer[100];
	scanf("%[^\n]%*c", buffer);
	while (buffer[0] != '-')
	{
		err = 0;
		ch = buffer;
		E();
		if (err || *ch != '\0')
			printf("NOT ACCEPTED\n");
		else
			printf("ACCEPTED\n");
		scanf("%[^\n]%*c", buffer);
	}
}
