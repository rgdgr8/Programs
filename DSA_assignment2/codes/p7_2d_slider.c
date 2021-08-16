#include<stdio.h>
#include<stdlib.h>
#define ledge 5 //using 5 instead of 128 because inputting so many values is unviable
#define sedge 3 //we use size 3 for the smaller matrix, we can easily show with size 5 also
#define size ((ledge)+2*((sedge)/2)) //for calculating the edge size of the padded larger matrix

void print(int sz,int x[][sz],char* const s){
  printf("%s\n",s);
  for(int k=0;k<sz;k++){
     for(int m=0;m<sz;m++)
        printf("%d ",x[k][m]);
    printf("\n");
  }
}

// utility function for multiplying 2 smaller matrices and returning the total sum of each indiviual products
int mul(int a[][sedge],int b[][sedge]){
  int tot = 0;

  for(int i=0;i<sedge;i++){
     int sum = 0;//stores the sum of the elements of each row of the product matrix of a*b
     for(int j=0;j<sedge;j++){
        sum += a[i][j]*b[j][i];
     }
     tot += sum;//stores the sum of the sums of rows 
  }
//  printf("tot=%d\n",tot);
  return tot;//return the total sum of the elements of the product matrix
}

/* main algorithm */
void mmul(int a[][size],int b[][sedge],int c[][ledge]){
  for(int i=0;i<ledge;i++){
     for(int j=0;j<ledge;j++){
        int d[sedge][sedge];
        for(int k=0;k<sedge;k++){
            for(int m=0;m<sedge;m++){
                d[k][m] = a[i+k][j+m];//save the smaller matrix of required size from the bigger matrix
//                printf("%d ",d[k][m]);
            } 
  //          printf("\n");
        }
        c[i][j] = mul(b,d);//fill up each index of the final required matrix with the total sum of the elements of each product matrix.
     }
  }
}

int main()
{
 //printf("%d\n",size);
 int a[size][size];   /*= {0, 0, 0, 0, 0, 0, 0,
                        0, 1, 2, 3, 4, 5, 0,
                        0, 6, 7, 8, 9,10, 0,
                        0,11,12,13,14,15, 0,
                        0,16,17,18,19,20, 0,
                        0,21,22,23,24,25, 0,
                        0, 0, 0, 0, 0, 0, 0};*///sedge/2 size padding around the matrix given to that boundary windows can be filled easily
 /* filling up the larger matrix to look like the matrix above */
 int padding = sedge/2;
 int k = 1;
 for(int i = 0; i < size; i++){
     for(int j = 0; j < size; j++){
	 if(i>=ledge || j>=ledge || i<padding || j<padding)
		 a[i][j] = 0;
	 else
		 a[i][j] = k++;
     }
 }
 print(size,a,"Larger matrix:");

 /* smaller matrix */
 int b[sedge][sedge] = {1,2,3,
                        4,5,6,
                        7,8,9};
 int c[ledge][ledge];
 mmul(a,b,c); 
 print(ledge,c,"Final matrix:");
 return 0;
}
