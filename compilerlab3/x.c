#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*
 
 * Grammar for accepting algebraic expression(for addition and multiplication)
 * and/or identifier names starting with an english letter (without whitespaces)
 	
 	E –> E + T | E - T | T 
	T –> T * F | T/F | F 
	F –> ( E ) | id

 * Same Grammar after left recursion removal
 
	E->TE'
	E'->+TE'|e
	T->FT'
	T'->*FT'|e
	F->id|const|(E)

*/

#include <string.h>

char *ch;
int err, len, count;
char pre[1000] = {0}, stack[1000];
;
void printstack()
{
	int l = count;
	while (l--)
		printf("%c", stack[l]);
}
void addtostack(const char *str, int l)
{
	while (l--)
		stack[count++] = str[l];
}
void E();
void E_();
void T();
void T_();
void F();

void E()
{
	count--;
	printf("=>");
	addtostack("TE'", 3);
	printf("%s", pre);
	printstack();
	printf("\n");
	T();
	if (err)
		return;
	E_();
}

void E_()
{
	count -= 2;
	printf("=>");
	if (*ch == '+')
	{
		pre[len++] = '+';
		addtostack("TE'", 3);
		printf("%s", pre);
		printstack();
		printf("\n");
		ch++;
		T();
		if (err)
			return;
		E_();
	}
	else if (*ch == '-')
	{

		pre[len++] = '-';
		addtostack("TE'", 3);
		printf("%s", pre);
		printstack();
		printf("\n");
		ch++;
		T();
		if (err)
			return;
		E_();
	}
	else
	{
		printf("%s", pre);
		printstack();
		printf("\n");
		return;
	}
}
void T()
{
	count--;
	printf("=>");
	addtostack("FT'", 3);
	printf("%s", pre);
	printstack();
	printf("\n");
	F();
	if (err)
		return;
	T_();
}
void T_()
{
	count -= 2;
	printf("=>");
	if (*ch == '*')
	{
		pre[len++] = '*';
		addtostack("FT'", 3);
		printf("%s", pre);
		printstack();
		printf("\n");
		ch++;
		F();
		if (err)
			return;
		T_();
	}
	else if (*ch == '/')
	{
		pre[len++] = '/';
		addtostack("FT'", 3);
		printf("%s", pre);
		printstack();
		printf("\n");
		ch++;
		F();
		if (err)
			return;
		T_();
	}
	else
	{
		printf("%s", pre);
		printstack();
		printf("\n");
		return;
	}
}
void F()
{
	count--;
	printf("=>");
	if (isalpha(*ch))
	{
		strcpy(pre + len, "id");
		len += 2;
		printf("%s", pre);
		printstack();
		printf("\n");

		while (isalnum(*ch) || *ch == '_')
			ch++;
	}
	else if (isdigit(*ch))
	{
		strcpy(pre + len, "const");
		len += 5;
		printf("%s", pre);
		printstack();
		printf("\n");
		while (isdigit(*ch))
			ch++;
	}
	else if (*ch == '(')
	{
		pre[len++] = '(';
		printf("%s", pre);
		addtostack("E)", 2);
		printstack();
		printf("\n");
		ch++;
		E();
		pre[len++] = ')';
		count--;
		if (*ch == ')')
			ch++;
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
		len = count = 0,
		memset(pre, '\0', 1000);
		printf("  E\n");
		stack[count++] = 'E';
		E();
		if (err || *ch != '\0')
			printf("NOT ACCEPTED\n");
		else
			printf("ACCEPTED\n");
		scanf("%[^\n]%*c", buffer);
	}
}
