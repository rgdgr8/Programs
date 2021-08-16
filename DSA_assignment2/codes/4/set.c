#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#define MAX 10
#define hash(a,b,x) (a*x+b)%MAX //has function defined here

int a,b;

typedef struct my_set{//hashtable bucket structure, where h points to the first element in a bucket and t points to the last element in that bucket, **************node structure is taken from list.h***************
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

int is_in_set(my_set* x,int key){//checks the presence of an element in a set
	int t = hash(a,b,key);
	if(search(x[t].h,key) != NULL)
	   return 1;
	return 0;
}

int main() {
 a = rand();b = rand(); //randomly generate hashing variables
 my_set* a = (my_set*)malloc(MAX*sizeof(my_set));
 my_set* b =  (my_set*)malloc(MAX*sizeof(my_set));
 create(&(a->h),&(a->t));
 create(&(b->h),&(b->t));

 printf("Select an option:\n1. insert\n2. delete\n3. search\n4. union\n5. intersection\n0. Exit\n");
 int op = 0;
 int x = 0;
 scanf("%d",&op);
 while(op!=0){
  switch(op){
	case 1: printf("Set 1 or 2? ");
		scanf("%d",&op);
		printf("Enter value: ");
		scanf("%d",&x);
		op==1 ? insert(a,x) : insert(b,x);
		op==1 ? print(a,"1") : print(b,"2");
		break;
	case 2: printf("Set 1 or 2? ");
		scanf("%d",&op);
		printf("Enter value: ");
		scanf("%d",&x);
		op==1 ? del(a,x) : del(b,x);
		op==1 ? print(a,"1") : print(b,"2");
		break;
	case 3: printf("Set 1 or 2? ");
		scanf("%d",&op);
		printf("Enter value: ");
		scanf("%d",&x);
		x = (op==1 ? is_in_set(a,x) : is_in_set(b,x));
		x==1 ? printf("is in set\n") : printf("is not in set\n");
		break;
	case 4: {
 		my_set* c = (my_set*)malloc(MAX*sizeof(my_set));
		create(&(c->h),&(c->t));
		Union(a,b,c);
		print(c,"Union of 1 and 2");
		break;
		}
	case 5: {
 		my_set* c = (my_set*)malloc(MAX*sizeof(my_set));
		create(&(c->h),&(c->t));
		intersection(a,b,c);
		print(c,"Intersection of 1 and 2");
		break;
		}
	default: return 0;
  }
  printf("Select an option:\n1. insert\n2. delete\n3. search\n4. union\n5. intersection\n0. Exit\n");
  scanf("%d",&op);
 }
}
