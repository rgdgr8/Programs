#include<stdio.h>
#include<stdlib.h>
int main()
{
 int a = 3;
 int *p = &a;
 int **pp = &p;
 printf("Printing using p: a=%d\n",*p);
 printf("Printing using pp: a=%d\n",**pp);
 return 0;
}
