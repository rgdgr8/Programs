#include<stdio.h>
#include"string.h"

int main()
{
 STRING x,y,z;
 initialize(&x,"ola");
 initialize(&y,"");
 initialize(&z,"");
 printf("x=\n");
 printf("%s\n",x.s);
 printf("%d\n",x.size);
 
 assign(&y,&x);
 printf("y=\n");
 printf("%s\n",y.s);
 printf("%d\n",y.size);

 z = concatenate(&x,&y);
 printf("z=\n");
 printf("%s\n",z.s);
 printf("%d\n",z.size);
 return 0;
}
