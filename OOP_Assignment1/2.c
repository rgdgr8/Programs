#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
int main()
{
 int size;
 do{
   printf("Enter valid size of array: ");
   scanf("%d",&size);
 }while(size<0 && size>INT_MAX);
 
 int *arr = (int*)malloc(size*sizeof(int));
 for(int i=0;i<size;i++){
    printf("Enter a integer value: ");
    scanf("%d",(arr+i));
 }
 
 for(int i=0;i<size;i++)
     printf("%d ",*(arr+i));
 printf("\n");
 return 0;
}
