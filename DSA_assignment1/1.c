#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//iterative method
void it(int n){
 long long f=1;
 for(int i=1;i<=n;i++){
    f*=i;
 }
 printf("%d! iteratively = %lld\n",n,f);
}

long long rec(int n){//recursive method
 if(n==1 || n==2)
   return n;
 else
   return n*rec(n-1);
}

int main()
{
 int repeat;
 do{
 printf("Enter an positive integer for factorial: ");
 int n; 
 scanf("%d",&n);
 it(n);
 printf("%d! recursively = %lld\n",n,rec(n));
 printf("Press 1 to repeat or 0 to stop: ");
 scanf("%d",&repeat);
 }while(repeat>0);
 return 0;
}
