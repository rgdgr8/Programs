#include "polynomial.h"

int main(void){
 int in;
 initiate();
 do{
   printf("Enter a value (0=cancel, 1=add, 2=multiply, 3=multiply with constant): ");
   scanf("%d",&in);
   switch(in){
     case 1: {polynomial a,b;insert(&a);insert(&b);print(padd(a,b));break;}
     case 2: {polynomial a,b;insert(&a);insert(&b);print(pmul(a,b));break;}
     case 3: {polynomial a;float f = 0;
             insert(&a);
             printf("Enter a constant for multiplication: ");
             scanf("%f",&f);
             print(const_mul(f,a));
             break;}
     default: return 0;
   }
 }while(in!=0);
 return 0;
}
