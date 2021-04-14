#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100000

int main()
{
   printf("Specify output file for storing strings: ");
   char *fname = malloc(30);
   scanf("%s",fname);
   FILE *ptr = fopen(fname,"w");
   char strings[MAX][10];
   int count =0;
   while(count<MAX){//while 100000 numbers have not been stored in file
      for(int i=0;i<9;i++){//for 9 charactered string (10th for sentinel value)
       char x = (rand()%26)+65;
       strings[count][i] = x;
      }
      strings[count][9] = '\0';//set sentinel 
      int flag= 0;
      for(int i=0;i<count;i++){
         if(strcmp(strings[i],strings[count])==0){//check if the generated string is duplicate
           flag=-1;//if yes, set flag and break
           break;
         }
      }
      if(flag==0){//if flag not set, i.e. generated string not duplicate
        fprintf(ptr,"%s\n",strings[count]);//store in file
        count++;
      }
   }
   fclose(ptr);
   return 0;
}
