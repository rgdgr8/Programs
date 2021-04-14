#include <stdio.h>

long long fib_it(int n){//iterative method
  int prev = 0;
  int sum = 1;
  for(int i=1;i<n;i++){
     int x = sum;
     sum += prev;
     prev = x;
  }
  return sum;
}

long long fib_rec(int n){
  if(n<=1)
    return n;
  
  return (fib_rec(n-1) + fib_rec(n-2));
}

int main()
{
 int repeat;
 do{
 printf("Enter an non-negative integer for fibonacci: ");
 int n; 
 scanf("%d",&n);
 printf("%dth fibonacci itertively = %lld\n",n,fib_it(n));
 printf("%dth fibonacci recursively = %lld\n",n,fib_rec(n));
 printf("Press 1 to repeat or 0 to stop: ");
 scanf("%d",&repeat);
 }while(repeat>0);
 return 0;
}
