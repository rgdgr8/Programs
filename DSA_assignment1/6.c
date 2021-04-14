#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct students{long roll; char *name;}students;

void merge(students stds[],int start,int m,int end){//routine for merging 
  int i=0,j=0,k=start;
 // printf("start = %d, m = %d, end = %d\n",start,m,end);
  int x_size = (m-start+1);
  int y_size = end-m;
  long x[x_size];
  long y[y_size];
  
  for(int l=0;l<x_size;l++){
    // printf("l=%d  start+i=%d\n",l,(start+i));
     x[l] = stds[start+l].roll;
  }
  for(int n=0;n<y_size;n++){
    // printf("n=%d  m+1+n=%d\n",n,(m+1+n));
     y[n] = stds[(m+1+n)].roll;
  }

  while(i<x_size && j<y_size){
       if(x[i]>y[j])
         stds[k++].roll = y[j++];
       else
         stds[k++].roll = x[i++];
  }
  
  while(i<x_size)
     stds[k++].roll = x[i++];
  while(j<y_size)
     stds[k++].roll = y[j++];
}
void sort(students stds[],int start,int end){//routine for merge sort 
  if(start>=end)
    return;
  
  int m = (start+end)/2;
  sort(stds,start,m);
  sort(stds,m+1,end);
  merge(stds,start,m,end);
}
 
int* smallest(students stds[],int count){//finding the smallest name(s)
  static int name_indexes[90];
  int index;
  int min = 101;
  for(int i=0;i<count;i++){
     int x = strlen(stds[i].name);
     if(x<min){//if name length is smaller than the current smallest
       index = 1;//come back to the 1st index
       min = x;
       name_indexes[index++] = i;
     }else if(x==min)//if name length is equal to the current smallest
       name_indexes[index++] = i;//add behind the current name in the array
  }
  name_indexes[0] = index;//store array length in 0th index
  return name_indexes;
}

int* largest(students stds[],int count){//finding the largest name(s)
  static int name_indexes[90];
  int index;
  int max = -1;
  for(int i=0;i<count;i++){
     int x = strlen(stds[i].name);
     if(x>max){//if name length is larger than the current largest
       index = 1;//come back to the 1st index
       max = x;
       name_indexes[index++] = i;
     }else if(x==max)//if name length is equal to the current largest
       name_indexes[index++] = i;//add behind the current name in the array
  }
  name_indexes[0] = index;//store array length in 0th index
  return name_indexes;
}

int main()
{ 
 students stds[90];
 printf("Specify file with Students info: ");
 char *file= malloc(30);
 scanf("%s",file);
 FILE *ptr = fopen(file,"r");
 FILE *ptr2 = fopen("mates.txt","w");
 int index = 0;
 while(index<90 && !feof(ptr)){//read the file and store in array
      unsigned long roll;
      char *name = malloc(100);
      fscanf(ptr,"%lu",&roll);
      fgets(name,100,ptr);
      stds[index].roll = roll;
      stds[index++].name = name;
 }
 sort(stds,0,index-1);//sort the array by roll number
 int *s = smallest(stds,index);
 int *l = largest(stds,index);
 printf("The smallest name(s) is/are:\n");
 for(int i=1;i<*s;i++){
    printf("%s\t",stds[*(s+i)].name);
    if(i!=0 && i%5==0)
      printf("\n");
 }
 printf("\nThe largest name(s) is/are:\n");
 for(int i=1;i<*l;i++){
    printf("%s\t",stds[*(l+i)].name);
    if(i!=0 && i%5==0)
      printf("\n");
 }
 for(int i=0;i<index;i++)//store in file in ascending order of roll
    fprintf(ptr2,"%lu\t %s\n",stds[i].roll,stds[i].name);
 fclose(ptr);
 fclose(ptr2);
 return 0;
}
