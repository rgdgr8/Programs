#include<stdio.h>
#include"string.h"

int main()
{
 STRING a,b,c;
 initialize(&c,"");

 printf("Select an option:\n1. assign value to string\n2. interchange string values\n3. concatenate two strings\n4. Compare 2 strings\n0. Exit\n");
 int op = 0;
 char x[50];
 scanf("%d",&op);
 while(op!=0){
	 switch(op){
		 case 1: printf("Enter value: ");
			 scanf(" %[^\n]%*c",x);
			 initialize(&a,(char*)x);
			 print_STR(&a,"string:");
			 break;
		 case 2: printf("Enter first value: ");
			 scanf(" %[^\n]%*c",x);
			 printf("string1 = %s",x);
			 initialize(&a,(char*)x);
			 printf("\n");

			 printf("Enter second value: ");
			 scanf(" %[^\n]%*c",x);
			 printf("string2 = %s\n",x);
			 initialize(&b,(char*)x);
			 assign(&c,&a);
			 assign(&a,&b);
			 assign(&b,&c);
			 print_STR(&a,"string1:");
			 print_STR(&b,"string2:");
			 break;

		 case 3: printf("Enter first value: ");
			 scanf(" %[^\n]%*c",x);
			 printf("string1 = %s",x);
			 initialize(&a,(char*)x);
			 printf("\n");

			 printf("Enter second value: ");
			 scanf(" %[^\n]%*c",x);
			 printf("string2 = %s\n",x);
			 initialize(&b,(char*)x);

			 c = concatenate(&a,&b);
			 print_STR(&c,"string1+string2:");
			 break;
		
		 case 4: printf("Enter first value: ");
			 scanf(" %[^\n]%*c",x);
			 printf("string1 = %s",x);
			 initialize(&a,(char*)x);
			 printf("\n");

			 printf("Enter second value: ");
			 scanf(" %[^\n]%*c",x);
			 printf("string2 = %s\n",x);
			 initialize(&b,(char*)x);

			 int y = compare_STR(&a,&b);
			 if(y<0)
				 printf("%s > %s",b.s,a.s);
			 else if(y==0)
				 printf("%s == %s",b.s,a.s);
			 else
				 printf("%s < %s",b.s,a.s);
			 break;
		
		 default: return 0;
	}
	printf("\n");
 	printf("Select an option:\n1. assign value to string\n2. interchange string values\n3. concatenate two strings\n4. Compare 2 strings\n0. Exit\n");
	scanf("%d",&op);
 }
}
