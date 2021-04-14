#include <stdio.h>
#include <stdlib.h>

/*********Defining macro to use generics in c***********/

#define my_merge(x,y,data,x_size,y_size)\
  int k=0,i=0,j=0; /* indexes for data,x,y */ \
  while(i<x_size && j<y_size){\
       if(x[i]>y[j]) /* if x[i] is greter put x[i] in data first and vice versa */ \
         data[k++] = y[j++];\
       else\
         data[k++] = x[i++];\
  }\
 /* empty out the rest of x or x if left*/ \
  while(i<x_size)\
     data[k++] = x[i++];\
  while(j<y_size)\
     data[k++] = y[j++];\


int main(){
  float a[] = {1.5,3.5,5.5,7.5,9.5};
  float b[] = {2.5,4.5,6.5,8.5};
  char* res[6];
  int c[] = {1,3,5,7,9};
  int d[] = {2,4,6,8};
  char* e[] = {"aaa","ccc","eee"};
  char* f[] = {"bbb","ddd","fff"};
  //for(int i=0;i<3;i++){
    // e[i] = malloc(30);
    // f[i] = malloc(30);
  //}
  my_merge(e,f,res,3,3);
  for(int i=0;i<6;i++)
     printf("%s ",res[i]);
  printf("\n");
}
