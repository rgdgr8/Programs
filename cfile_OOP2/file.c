#include<stdio.h> 
#include<stdlib.h>

int rollcheck(int newroll,int search);//check wheather the roll is already in file
void add();
void removedata();
void show();
void edit();
void fsearch();//search for an entry

typedef struct student {
 int roll;
 char name[30];
 int mark1,mark2,mark3,mark4,mark5;
 int present;
}student;

int main() {
  FILE* fp = fopen("students.dat","w+");//clear the file
  fclose(fp);

 while(1) {
   fflush(stdin);
   char ch;
   printf("enter a value:\n1. add\n2. delete\n3. search\n4. edit\n5. print\n0. exit\nYour Choice = ");
  scanf("%c",&ch); 
  switch(ch){
   case '0':return 0; 
   case '1':{add();break; }
   case '2':{removedata();break; }
   case '3':{fsearch();break; }
   case '4':{edit();break; }
   case '5':{show();break; }
   default: {printf("\n\nwrong input\n\n"); return 0; }
  }
 }
}

void print(student *s){//helper function for show() and fsearch()
  if(s->present==0){
    printf("No such data\n");
    return;
  }
  printf("Roll: %d, Name: %s\n",s->roll,s->name);
  printf("Marks in Math English Physics Chemistry Biology respectively:\n");
  printf("%d\n",s->mark1);
  printf("%d\n",s->mark2);
  printf("%d\n",s->mark3);
  printf("%d\n",s->mark4);
  printf("%d\n",s->mark5);
}

void show(){
  FILE* fp = fopen("students.dat","r");student demo;
  while(fread(&demo,sizeof(student),1,fp)>0){
     if(demo.present==1)
       print(&demo);
  }
}

void fsearch(){
  int roll;
  printf("Enter roll to search for: ");
  scanf("%d",&roll);
  rollcheck(roll,1);
}

int rollcheck(int newroll, int search){
  FILE* fp=NULL; student demo;
  fp=fopen("students.dat","rb"); 
  if(fp==NULL){
    fprintf(stderr,"\nError in openig file\n"); exit(1);
  }
  while(fread(&demo,sizeof(student),1,fp)){
       if(demo.roll==newroll && demo.present==1) {
         if(search==1)//for fsearch()
            print(&demo);
         fclose(fp);
         return 1; 
       }
   } 
   fclose(fp); return 0;
}

void add(){
 FILE *fp=NULL;
 student newinfo;
 fp=fopen("students.dat","ab+"); 
 if(fp==NULL){
   fprintf(stderr,"\nError in openig file\n");exit(1); }
 do{
   printf("enter the roll of the new student(enter a unique roll) "); scanf("%d",&newinfo.roll);
 }while(rollcheck(newinfo.roll,0));
 printf("enter the name of the student\t"); scanf(" %[^\n]s",newinfo.name);
 printf("enter the marks of \nMath English Physics Chemistry Biology in a secuence \n");
 scanf("%d %d %d %d %d",&newinfo.mark1,&newinfo.mark2,&newinfo.mark3,&newinfo.mark4,&newinfo.mark5);
 newinfo.present = 1;
 fwrite(&newinfo,sizeof(student),1,fp);
 fclose(fp);
}
   
void removedata(){
 FILE *fp1=NULL;student demo;
 int roll;
 printf("enter the roll you want to delete "); scanf("%d",&roll);
 if(rollcheck(roll,0)==0) {
   printf("\n\nYour entered roll is not found\n");
   return;
 }
 fp1 = fopen("students.dat","rb+");
 if(fp1==NULL){
    fprintf(stderr,"\nError in openig file \n"); exit(1);
 }
 while(fread(&demo,sizeof(student),1,fp1)) {
   if(demo.roll==roll && demo.present==1) {//if found and not logically deleted
     fseek(fp1,-1*sizeof(student),SEEK_CUR);//go back
     demo.present = 0;//logical delete
     fwrite(&demo,sizeof(student),1,fp1);//overwrite
   }
 } 
 fclose(fp1);
}

void edit(){
 FILE *fp1=NULL;student demo;
 int roll;
 printf("enter the roll you want to edit "); scanf("%d",&roll);
 if(rollcheck(roll,0)==0) {
   printf("\n\nYour entered roll is not found\n");
   return;
 }
 fp1 = fopen("students.dat","rb+");
 int e;
 printf("Enter field you want to edit(1 for name, 2 for marks, any other key to cancel): ");
 scanf("%d",&e);
 if(e!=1 && e!=2)
    return;

 if(fp1==NULL){
    fprintf(stderr,"\nError in openig file \n"); exit(1);
 }
 while(fread(&demo,sizeof(student),1,fp1)) {
   if(demo.roll==roll && demo.present==1) {//if found and not logically deleted
     if(e==2){//change marks
        printf("new marks for maths(0 to go to next subject): ");
        scanf("%d",&e);
        if(e>0)
          demo.mark1 = e;
        printf("new marks for english(0 to go to next subject): ");
        scanf("%d",&e);
        if(e>0)
          demo.mark2 = e;
        printf("new marks for physics(0 to go to next subject): ");
        scanf("%d",&e);
        if(e>0)
          demo.mark3 = e;
        printf("new marks for chemistry(0 to go to next subject): ");
        scanf("%d",&e);
        if(e>0)
          demo.mark4 = e;
        printf("new marks for biology(0 to go to cancel): ");
        scanf("%d",&e);
        if(e>0)
          demo.mark5 = e;
     }else{//change name
       printf("New name: ");
       scanf(" %[^\n]s",demo.name);
     }
     fseek(fp1,-1*sizeof(student),SEEK_CUR);//go back
     fwrite(&demo,sizeof(student),1,fp1); //overwrite
   }
 } 
 fclose(fp1);
}
