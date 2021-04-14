#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 100000

int main()
{
   printf("Specify output file for storing integers: ");
   char *fname = malloc(30);
   scanf("%s",fname);
   FILE *ptr = fopen(fname,"w");
   int nums[MAX];//to store the occurrence of the same numbers
   int count =0;
   while(count<MAX){//while not all 100000 numbers have been stored
       int x = rand()%MAX+1;//generate random numbers
       if(nums[x-1]==0){//if the number was not generated before
          nums[x] = 1;
          count++;
          fprintf(ptr,"%d\n",x);//store in file
       }
   }
   fclose(ptr);
   return 0;
}
