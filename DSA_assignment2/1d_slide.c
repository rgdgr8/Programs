#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define type(T) _Generic( (T), char: " %c ", int: "%d ", float: "%.3f ", default: "%s")
//generic printing function
#define print(a,size)\
  for(int i=0;i<size;i++)\
     printf(type(a[i]),a[i]);\
  printf("\n");\

void max(int * a,int size,int *b,int k){
  int i = 0,j = 0;
  int max = -1;
  int t = k;
  while(i<t){
    if(a[i]>max)
      max = a[i];
    i++;
    if(i==t){
      b[j++] = max;
      if(t+1<=size){
         t++;
         i = j;
         max = -1;
      }
    }
  }
}

void min(int * a,int size,int *b,int k){
  int i = 0,j = 0;
  int min = INT_MAX;
  int t = k;
  while(i<t){
    if(a[i]<min)
      min = a[i];
    i++;
    if(i==t){
      b[j++] = min;
      if(t+1<=size){
         t++;
         i = j;
         min = INT_MAX;
      }
    }
  }
}

int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void median(int *a,int size,int *b,int k){
  for(int i=0;i<(size-k+1);i++){
     int c[k];int z = 0;
     for(int j=i;j<(i+k);j++)
        c[z++] = a[j];
     qsort(c, k, sizeof(int), cmp);
     //print(c,k);
     b[i] = c[(k/2)];
  }
}

void avg(int *a,int size,float *b,int k){
  for(int i=0;i<(size-k+1);i++){
     float sum = 0;
     for(int j=i;j<(i+k);j++)
        sum += a[j];
     b[i] = sum/k;
  }
}

int main()
{ 
 int a[] = {4, 5, 1, 13, 3, 25, 27, 18, 10, 3, 4, 9};
 int size = sizeof(a)/sizeof(a[0]);
 //printf("size=%d\n",size);
 int k = 3;
 int b[size-k+1];
 float c[size-k+1];
 //max(a,size,b,k);
 //print(b,size-k+1);
 //min(a,size,b,k);
 //print(b,size-k+1);
 median(a,size,b,k);
 print(b,size-k+1);
 avg(a,size,c,k);
 print(c,size-k+1);
 return 0;
}
