#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct x{
  char s[30];
}X;

int main()
{
 X a,b;
 strcpy(a.s,"ola");
 b = a;
 printf("%s\n",a.s);
 printf("%s\n",b.s);
 
 strcpy(b.s,"kola");
 printf("%s\n",a.s);
 printf("%s\n",b.s);

 return 0;
}
