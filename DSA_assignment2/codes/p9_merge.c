#include <stdio.h>
#include <stdlib.h>

/*********Defining macro to use generics in c, still can't be used for c-strings, as comparing strings is quite different from comparing numericals. But, we can easily achieve c-string array merging by writing a function which compares string character by character (like strcmp() in c) ***********/
int k,i,j;
#define my_merge(x,y,data,x_size,y_size)\
  k=0,i=0,j=0; /* indexes for data,x,y */ \
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

/* Generic function for printing arrays of different basic data types */
#define type(T) _Generic((T), char: " %c ", int: "%d ", float: "%f ",default: "%s ")
#define print(a,sz)\
	for(int i=0;i<sz;i++)\
		printf(type(a[i]),a[i]);\
	printf("\n");\

int main(){
  float a[] = {1.5,3.5,5.5,7.5,9.5};
  float b[] = {2.5,4.5,6.5,8.5};
  print(a,(sizeof(a)/sizeof(a[i])))
  print(b,(sizeof(b)/sizeof(b[i])))
  float ab[10];
  my_merge(a,b,ab,5,5);
  print(ab,10);

  int c[] = {1,3,5,7,9};
  int d[] = {2,4,6,8};
  print(c,(sizeof(c)/sizeof(c[i])))
  print(d,(sizeof(d)/sizeof(d[i])))
  int cd[9];
  my_merge(c,d,cd,5,4);
  print(cd,9);
}
