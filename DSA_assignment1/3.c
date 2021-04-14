#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* macro function used so that lin_search can be generic for interger and flaoting point types*/
#define lin_search(arr,size,key)\
   int flag = 0;\
   for(int i=0;i<size;i++)\
       if(arr[i]==key){\
         x=i;flag=1;}\
   if(flag==0)\
     printf("Not found\n");\

void lin_search_str(char **arr,int size,char *key){//linear search for strings
   for(int i=0;i<size;i++){
       if(strcmp(arr[i],key)==0){
         printf("array[%d] = %s\n",i,arr[i]);exit(0);}
   }
   printf("Not found\n");
}

int bin_search(int *arr,int key,int l,int r){//binary search for integers
   if(l>r)
     return -1;
   
   int mid = (l+r)/2;
   if(arr[mid]==key)
     return mid;

   if(arr[mid]>key)
     return bin_search(arr,key,l,mid-1);
   else
     return bin_search(arr,key,mid+1,r);
}
int bin_search_fl(float *arr,float key,int l,int r){//binary search for floats
   if(l>r)
     return -1;
   
   int mid = (l+r)/2;
   if(arr[mid]==key)
     return mid;

   if(arr[mid]>key)
     return bin_search_fl(arr,key,l,mid-1);
   else
     return bin_search_fl(arr,key,mid+1,r);
}
int bin_search_str(char **arr,char* key,int l,int r){//binary search for strings
   if(l>r)
     return -1;
   
   int mid = (l+r)/2;
   if(strcmp(arr[mid],key)==0)
     return mid;

   if(strcmp(arr[mid],key)>0)
     return bin_search_str(arr,key,l,mid-1);
   else
     return bin_search_str(arr,key,mid+1,r);
}

int main()
{ 
 int arr[] = {1,2,3,4,5};
 float arr2[] = {1.5,2.5,3.5,4.5,5.5};
 int x = 0;
 lin_search(arr,5,5);printf("arr[%d] = %d\n",x,arr[x]);
 x = bin_search_fl(arr2,5.5,0,4);
 if(x<0)
   printf("Not found\n");
 else
   printf("array[%d] = %d\n",x,arr[x]);

 char* c[] = {"fine","ok","yes"};
 //lin_search_str(c,3,"ola");
 x = bin_search_str(c,"fine",0,2);
 if(x<0)
   printf("Not found\n");
 else
   printf("c[%d] = %s\n",x,c[x]);
 return 0;
}
