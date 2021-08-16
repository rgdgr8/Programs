#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define type(T) _Generic( (T), char: " %c ", int: "%d ", float: "%.3f ", default: "%s")
//generic printing function
#define print(a,size,s)\
  printf("%s",s);\
  for(int i=0;i<size;i++)\
     printf(type(a[i]),a[i]);\
  printf("\n");\

void max(int * a,int size,int *b,int k){//max filter, k is the window size, a is the array, b is the window, size is the size of the array a
  int i = 0,j = 0;
  int max = -1;
  int t = k;
  while(i<t){//find max element in the current window
    if(a[i]>max)
      max = a[i];
    i++;
    if(i==t){//if whole current window has been traversed
      b[j++] = max;//save max element of each window of size k in b
      if(t+1<=size){//if there is space left to slide in array a
         t++;//slide the window
         i = j;//update index of sub-array/window b
         max = -1;//reset value of max, to start searching for max value in the current window again
      }
    }
  }
}

void min(int * a,int size,int *b,int k){//min filter, k is the window size, a is the array, b is the window, size is the size of the array a
  int i = 0,j = 0;
  int min = INT_MAX;
  int t = k;
  while(i<t){//find min element in the current window
    if(a[i]<min)
      min = a[i];
    i++;
    if(i==t){//if whole current window has been traversed
      b[j++] = min;//save min element of each window of size k in b
      if(t+1<=size){//if there is space left to slide in array a
         t++;//slide the window
         i = j;//update index of sub-array/window b
         min = INT_MAX;//reset value of min, to start searching for min value in the current window again
      }
    }
  }
}

/*function for using in qsort()*/
int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void median(int *a,int size,int *b,int k){//median filter, k is the window size, a is the array, b is the window, size is the size of the array a
  /* sort the window elements for each window position in a and store the middle/median values in b */
  for(int i=0;i<(size-k+1);i++){
     int c[k];int z = 0;
     for(int j=i;j<(i+k);j++)
        c[z++] = a[j];
     qsort(c, k, sizeof(int), cmp);
     //print(c,k);
     b[i] = c[(k/2)];
  }
}

void avg(int *a,int size,float *b,int k){//average filter, k is the window size, a is the array, b is the window, size is the size of the array a
  /* find average of the values for each window position in a and store in b */
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
 print(a,size,"original: ")
 //printf("size=%d\n",size);
 int k = 3;
 int b[size-k+1];
 float c[size-k+1];
 max(a,size,b,k);
 print(b,size-k+1,"max: ");
 min(a,size,b,k);
 print(b,size-k+1,"min: ");
 median(a,size,b,k);
 print(b,size-k+1,"median: ");
 avg(a,size,c,k);
 print(c,size-k+1,"average: ");
 return 0;
}
