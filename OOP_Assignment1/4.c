#include<stdio.h>
#include<stdlib.h>
int main()
{
 int x;
 do{
   printf("1D Array or 2D Array (1 for 1D, 2 for 2D) : ");
   scanf("%d",&x);
 }while(x!=1 && x!=2);
 
 if(x==1){
   int c;
   printf("Input number of elements in the 1D Array: ");
   scanf("%d",&c);
   int *arr = (int*)malloc(c*sizeof(int));
   for(int i=0;i<c;i++){
      printf("Enter value #%d: ",(i+1));
      scanf("%d",(arr+i));   
   }
   printf("The entered values are:\n");
   for(int i=0;i<c;i++)
      printf("%d ",arr[i]);
   printf("\n");
 }else{
   int r,c;
   printf("Input number of rows: ");
   scanf("%d",&r);
   printf("Input number of colums: ");
   scanf("%d",&c);
   int **arr = (int**)malloc(r*sizeof(int*));
   for(int i=0;i<r;i++)
      *(arr+i) = (int*)malloc(c*sizeof(int));
   for(int i=0;i<r;i++)
      for(int j=0;j<c;j++){
         printf("Enter value for %dth row and %dth column: ",(i+1),(j+1));
         scanf("%d",*(arr+i)+j);
      }
   printf("Values entered are displayed in matrix form as:\n");
   for(int i=0;i<r;i++){
      for(int j=0;j<c;j++){
         printf("%d ",arr[i][j]);
      }
      printf("\n");
   }
 }
      
 return 0;
}
