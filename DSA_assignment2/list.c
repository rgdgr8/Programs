#include<stdio.h>
#include<stdlib.h>
#include"list.h"

typedef struct list{
  node *h,*t;
}list;

void del(list l,int key){
  node *x = search(l.h,key);
  
  if(x==NULL)
     return;

  erase(&l.h,&l.t,x);
}

int main()
{
 list l;
 create(&l.h,&l.t);
 for(int i=0;i<3;i++)
    append(&l.h,&l.t,i);
 print_dll(l);printf("\n");
 for(int i=0;i<3;i++)
    insert_before(&l.h,&l.t,i,-i);
 print_dll(l);printf("\n");
 
 del(l,2);
 print_dll(l);printf("\n");
 return 0;
}
