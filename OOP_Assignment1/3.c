#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
 int r,c;
 printf("Enter Row size and Column size respectively with a space in between: ");
 scanf("%d %d",&r,&c);
 int (*a)[c]; //Pointer to Array Implementation.
 a=malloc(r*c*sizeof(int));

 int *p[r];//Array of Pointers Implementation.
 for(int i=0;i<r;i++)
    p[i] = malloc(c*sizeof(int));

for(int j=0;j<r;j++)
 for(int i=0;i<c;i++){
    printf("Enter an integer value: ");
    int x;
    scanf("%d",&x);
    *(*(a+j)+i) = x;//input inside pointer to arrays 
    *(*(p+j)+i) = x;//input inside arrays of pointers
 }
printf("Print pointer to arrays implementation\n");
for(int j=0;j<r;j++){//print pointer to arrays implementation
 for(int i=0;i<c;i++)
    printf("%d ",*(*(a+j)+i));
 printf("\n");
}
printf("Print arrays of pointers implementation\n");
for(int j=0;j<r;j++){//print arrays of pointers implementation
 for(int i=0;i<c;i++)
    printf("%d ",*(*(p+j)+i));
 printf("\n");
}
 return 0;
}
