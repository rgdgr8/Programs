#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#define MAX 10
#define hash(a,b,x) (a*x+b)%MAX

int a,b;

typedef struct my_set{
  node *h,*t;
}my_set;

/*void print_ht(my_set *dll){
   for(int i=0;i<MAX;i++){
      printf("%d : ",i);
      print_dll(dll[i]);
      printf("\n");
   }
  printf("\n");
}*/

void print(my_set *dll,char* s){//print set
   printf("%s: ",s);
   for(int i=0;i<MAX;i++){
      //printf("%d : ",i);
      print_dll(dll[i]);
   }
  printf("\n");
}

void del(my_set *dll,int key){//delete number from set
   int index = hash(a,b,key);//hashing to find index
   node *temp = search(dll[index].h,key);//search for node with key
   if(temp==NULL)//if not found cancel
     return;
  
   erase(&dll[index].h,&dll[index].t,temp);//deletion
}

void insert(my_set* dll,int key){//insert one entry into set
  int t = hash(a,b,key);//hashing to find index
  
  if(search(dll[t].h,key))//if already present return
     return;

  append(&dll[t].h,&dll[t].t,key);//insert in set
}

void insert_all(my_set* dll,int *arr,int size){//insert a group of entries in set
  for(int i=0;i<size;i++)
     insert(dll,arr[i]);
}

void Union(my_set* A,my_set* B,my_set* C){//union of two sets
   for(int i=0;i<MAX;i++){
      node* t = A[i].h;
      for(;t!=NULL;t=t->next)
         insert(C,t->s);
   }
   for(int i=0;i<MAX;i++){
      node* t = B[i].h;
      for(;t!=NULL;t=t->next)
         insert(C,t->s);
   }
}

void intersection(my_set* A,my_set* B,my_set* C){//intersection of two sets
   for(int i=0;i<MAX;i++){
      node* t = B[i].h;
      for(;t!=NULL;t=t->next){
         int tt = hash(a,b,t->s);
         node *x = search(A[tt].h,t->s);
         if(x)
           insert(C,x->s);
      }
   }
}

int main()
{
 a = rand();b = rand();
 int a[] = {1,2,3,4,5};
 int b[] = {4,5,8,9,10};

 my_set A[MAX],B[MAX],C[MAX],D[MAX];
 for(int i=0;i<MAX;i++){//create sets
     create(&A[i].h,&A[i].t);
     create(&B[i].h,&B[i].t);
     create(&C[i].h,&C[i].t);
     create(&D[i].h,&D[i].t);
 }

 insert_all(A,a,5);
 //print_ht(A);
 print(A,"A");

 insert_all(B,b,5);
 //print_ht(B);
 print(B,"B");

 Union(A,B,C);
 //print_ht(C);
 print(C,"C");

 intersection(A,B,D);
 //print_ht(D);
 print(D,"D");

 return 0;
}
