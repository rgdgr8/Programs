#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct person{
  int age;
  char name[100];
}person;

void sort(person people[],int p){
 for(int i=0;i<p;i++){
    for(int j=i;j<p;j++){
       if(people[i].age>people[j].age){
         person t = people[i];
         people[i] = people[j];
         people[j] = t;
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
 person people[p];
 for(int i=0;i<p;i++){
    printf("Enter name of person #%d: ",(i+1));
    scanf(" %[^\n]%*c",people[i].name);
    printf("Enter age of person #%d: ",(i+1));
    scanf("%d",(ages+i));
    people[i].age = ages[i];
 }
 sort(people,p);
 printf("Names and Ages are:\n");
 for(int i=0;i<p;i++){
    printf("%s  %d\n",people[i].name,people[i].age);
 }
 return 0;
}
