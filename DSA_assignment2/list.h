#include<stdio.h>
#include<stdlib.h>
#define LIST_FILE 1 //macro for include guard

typedef struct node{
 int s;
 struct node *next;
 struct node *prev;
}node;


void input(int *s){
 printf("Enter a Number: ");
 scanf("%d",s);
}

node *t;
/*macro function to make this printing function usable by different programs*/
#define print_dll(x)\
  t = x.h;\
  for(;t!=NULL;t=t->next)\
     printf("%d , ",t->s);\

void create(node **h,node** t){
 *h = NULL;
 *t = *h;
}

node* search(node*h,int x){
  for(;h!=NULL;h=h->next)
      if(h->s==x)
        return h;
  return NULL;
}

void append(node **h,node** t,int x){
   node *newNode = malloc(sizeof(node));
   newNode->s = x;
   newNode->next = NULL;
   if(*h==NULL || *t==NULL){
     newNode->prev = NULL;
     *h = newNode;
     *t = *h;
   }else{
     newNode->prev = *t;
     (*t)->next = newNode;
     *t = newNode;
   }
}

void insert_before(node **h,node **t,int before,int key){
   node *x = search(*h,before);
   
   if(x==NULL){
     append(h,t,key);
     return;
   }
   
   node* newNode = malloc(sizeof(node));
   newNode->s = key;
   newNode->next = x;

   if(x==*h){
     newNode->prev = NULL;
     (*h)->prev = newNode;
     *h = newNode;
     return;
   }

   newNode->prev = x->prev;
   x->prev->next = newNode;
   x->prev = newNode;
}

void erase(node **h,node** t,node* x){
   if(x==NULL)
     return;

   if(*h==x){
     if(*t==*h)
       *t = NULL;
     *h = (*h)->next;
     if(*h)
       (*h)->prev = NULL;
     free(x);
     return;
   }

   if(*t==x){
     *t = (*t)->prev;
     free(x);
     (*t)->next = NULL;
     return;
   }

   x->prev->next = x->next;
   x->next->prev = x->prev;
   free(x);
}
