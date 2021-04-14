#include<stdio.h>
#include<stdlib.h>

int sort_check(int *a,int size){
  int asc=0,desc=0;
  for(int i=1;i<size;i++){
     if(a[i]>=a[i-1])
       asc++;
     else
       desc++;
  }
  
  if(asc==size-1)
     return 1;
  
  if(desc==size-1)
    return 2;

  return 3;
}

void print(int x){
  switch(x){
    case 1: printf("Ascending order\n");break;
    case 2: printf("Descending order\n");break;
    case 3: printf("Random order\n");break;
    default: exit(0);
  }
}

int main()
{
 int a[] = {1,2,3,4,5}; 
 int b[] = {5,4,3,2,1}; 
 int c[] = {2,4,3,6,5}; 

 print(sort_check(a,5));
 print(sort_check(b,5));
 print(sort_check(c,5));
 
 return 0;
}
