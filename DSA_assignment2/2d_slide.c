#include<stdio.h>
#include<stdlib.h>
#define ledge 5
#define sedge 3
#define size ((ledge)+2*((sedge)/2))

void print(int sz,int x[][sz]){
  for(int k=0;k<sz;k++){
     for(int m=0;m<sz;m++)
        printf("%d ",x[k][m]);
    printf("\n");
  }
}

int mul(int a[][sedge],int b[][sedge]){
  int tot = 0;

  for(int i=0;i<sedge;i++){
     int sum = 0;
     for(int j=0;j<sedge;j++){
        sum += a[i][j]*b[j][i];
     }
     tot += sum;
  }
//  printf("tot=%d\n",tot);
  return tot;
}

void mmul(int a[][size],int b[][sedge],int c[][ledge]){
  for(int i=0;i<ledge;i++){
     for(int j=0;j<ledge;j++){
        int d[sedge][sedge];
        for(int k=0;k<sedge;k++){
            for(int m=0;m<sedge;m++){
                d[k][m] = a[i+k][j+m];
//                printf("%d ",d[k][m]);
            } 
  //          printf("\n");
        }
        c[i][j] = mul(b,d);
     }
  }
}

int main()
{
 //printf("%d\n",size);
 int a[size][size]   = {0, 0, 0, 0, 0, 0, 0,
                        0, 1, 2, 3, 4, 5, 0,
                        0, 6, 7, 8, 9,10, 0,
                        0,11,12,13,14,15, 0,
                        0,16,17,18,19,20, 0,
                        0,21,22,23,24,25, 0,
                        0, 0, 0, 0, 0, 0, 0};//sedge/2 size boundary around the matrix given
 
 int b[sedge][sedge] = {1,2,3,
                        4,5,6,
                        7,8,9};
 int c[ledge][ledge];
 mmul(a,b,c); 
 print(ledge,c);
 return 0;
}
