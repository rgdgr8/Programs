#include<stdio.h>
#include<stdlib.h>
#define max_terms 100

typedef struct sparse{
  int rows;
  int cols;
  int terms;
}sparse;

void transpose(sparse* a, sparse* b){
  int row_terms[a[0].cols];int start_indice[a[0].cols];
  b[0].rows = a[0].cols;b[0].cols = a[0].rows;b[0].terms = a[0].terms;

  for(int i=0;i<a[0].cols;i++)
     row_terms[i] = 0;
  for(int i=1;i<=a[0].terms;i++)
     row_terms[a[i].cols]++;
  
  start_indice[0] = 1;
  for(int i=1;i<a[0].cols;i++)
     start_indice[i] = start_indice[i-1] + row_terms[i-1];

  for(int i=1;i<=a[0].terms;i++){
     int j = start_indice[a[i].cols]++;
     b[j].rows = a[i].cols;
     b[j].cols = a[i].rows;
     b[j].terms = a[i].terms;
  }
}

void print(sparse* a,int r,int c,char *s){
  int x[r][c];
  for(int i=0;i<r;i++){
     for(int j=0;j<c;j++){
        x[i][j] = 0;
     }
  }
  printf("%s: %d %d %d\n",s,a[0].rows,a[0].cols,a[0].terms);
  for(int i=1;i<=a[0].terms;i++){
     x[a[i].rows][a[i].cols] = a[i].terms;
     printf("%d  %d  %d\n",a[i].rows,a[i].cols,a[i].terms);
  }
  printf("\n");

  for(int i=0;i<r;i++){
     for(int j=0;j<c;j++){
        printf("%d ",x[i][j]);
     }
     printf("\n");
  }
  printf("--------------------------------------\n");
}

void mmult(sparse *a,sparse *b,sparse *c){
  if(a[0].rows!=b[0].cols){
    printf("Incompatible matrix multiplication\n");
    return;
  }
  
  c[0].rows = a[0].rows;c[0].cols = b[0].cols;
  int count = 0;//for number of terms in c

  sparse d[b[0].terms+1];
  transpose(b,d);//transpose of b in d
//  print(d,d[0].rows,d[0].cols,"d");
  for(int i=1;i<=a[0].terms;){
     int r = a[i].rows;//curr row of result matrix
     for(int j=1;j<=d[0].terms;){
        int co = d[j].rows;//curr col of result matrix
        
        int ta = i;//temporary i
        int sum = 0;
//while ta and j are in bounds of a and d, and the rows and cols remain the same as r and co
        while(ta<=a[0].terms && j<=d[0].terms && a[ta].rows == r && d[j].rows == co){
             if(a[ta].cols<d[j].cols)
                ta++;//go to next col value of a
             else if(a[ta].cols>d[j].cols)
                j++;//go to next col value of d
             else
               sum += a[ta++].terms*d[j++].terms;//add product to sum
        }

        if(sum!=0){
          c[++count].rows = r; c[count].cols = co; c[count].terms = sum;
        }
        
        while(j<=d[0].terms && d[j].rows == co)// go to next row value of d
              j++;
     }
      
     while(i<=a[0].terms && a[i].rows == r)// go to next row value of a
          i++;
  }
  c[0].terms = count;
}

void madd(sparse* a,sparse* b,sparse* c){
  if(a[0].rows != b[0].rows || a[0].cols != b[0].cols){
    printf("Incompatible matrix addition\n");
    return;
  }

  c[0].rows = a[0].rows; c[0].cols = a[0].cols;
  int count = 0;

  int i=1,j=1;
  while(i<=a[0].terms && j<=b[0].terms){
     count++;
     printf("i=%d j=%d\n",i,j);
     if(a[i].rows<b[j].rows){
       c[count].rows = a[i].rows; c[count].cols = a[i].cols; 
       c[count].terms = a[i++].terms;
     }else if(a[i].rows>b[j].rows){
       c[count].rows = b[j].rows; c[count].cols = b[j].cols;
       c[count].terms = b[j++].terms;
     }else{
       if(a[i].cols<b[j].cols){
         c[count].rows = a[i].rows; c[count].cols = a[i].cols; 
         c[count].terms = a[i++].terms;
       }else if(a[i].cols>b[j].cols){
         c[count].rows = b[j].rows; c[count].cols = b[j].cols;
         c[count].terms = b[j++].terms;
       }else{
         c[count].rows = a[i].rows; c[count].cols = a[i].cols; 
         c[count].terms = a[i++].terms + b[j++].terms;
       }
     }
  }
  while(i<=a[0].terms){
    c[++count].rows = a[i].rows; c[count].cols = a[i].cols;
    c[count].terms = a[i++].terms;
  }
  while(j<=b[0].terms){
    c[++count].rows = b[j].rows; c[count].cols = b[j].cols;
    c[count].terms = b[j++].terms;
  }
  c[0].terms = count;
}
