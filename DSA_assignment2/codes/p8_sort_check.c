#include<stdio.h>
#include<stdlib.h>

int sort_check(int *a,int size){
  int asc=0,desc=0;
  for(int i=1;i<size;i++){
     if(a[i]>=a[i-1])
       asc++;//increment asc if next element is greater than the previous element
     else
       desc++;//increment dsc if next element is smaller than the previous element
  }
  
  if(asc==size-1)//if asc is equal to the number of elements-1
     return 1;//then the array is sorted in ascending order
  
  if(desc==size-1)//if asc is equal to the number of elements-1
    return 2;//then the array is sorted in ascending order

  return 3;//otherwise the array is in random order
}

void print(int x,int* y,int size){
  printf("Array: ");
  for(int i=0;i<size;i++)
	  printf("%d ",y[i]);
  switch(x){
    case 1: printf("is in Ascending order\n");break;
    case 2: printf("is in Descending order\n");break;
    case 3: printf("is in Random order\n");break;
    default: exit(0);
  }
}

int main()
{
 int a[] = {1,2,3,4,5}; 
 int b[] = {5,4,3,2,1}; 
 int c[] = {2,4,3,6,5}; 

 print(sort_check(a,5),a,5);
 print(sort_check(b,5),b,5);
 print(sort_check(c,5),c,5);
 
 return 0;
}
