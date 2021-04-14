#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sort(int ages[], char names[][100],int p){
 for(int i=0;i<p;i++){
    for(int j=i;j<p;j++){
       if(ages[i]>ages[j]){
         int t = ages[i];
         ages[i] = ages[j];
         ages[j] = t;
         char *s = malloc(100);
         strcpy(s,names[i]);
         strcpy(names[i],names[j]);
         strcpy(names[j],s);
       }
    }
 }
}

int main()
{
 int p;
 printf("Number of people?: ");
 scanf("%d",&p);
 int ages[p];
 char names[p][100];
 for(int i=0;i<p;i++){
    printf("Enter name of person #%d: ",(i+1));
    scanf(" %[^\n]%*c",names[i]);
    printf("Enter age of person #%d: ",(i+1));
    scanf("%d",(ages+i));
 }
 sort(ages,names,p);
 printf("Names and Ages are:\n");
 for(int i=0;i<p;i++){
    printf("%s  %d\n",names[i],ages[i]);
 }
 return 0;
}
