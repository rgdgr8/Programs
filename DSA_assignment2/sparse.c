#include "sparse.h"

int main(int argc,char* argv[])
{
 int r,c,t;
// FILE *fp = fopen(argv[1],"r");
 printf("Enter number of rows, columns and terms: ");
 scanf("%d %d %d",&r,&c,&t);
// r = 5,c =5,t = 5;
 sparse a[t+1],b[t+1];sparse *c2 = malloc(max_terms*sizeof(sparse));
 sparse *d = malloc(max_terms*sizeof(sparse));
 a[0].rows = r;a[0].cols = c;a[0].terms = t;
 for(int i=1;i<=a[0].terms;i++){
    printf("Enter row, column and term: ");
    scanf("%d %d %d",&r,&c,&t);
  //  fscanf(fp,"%d %d %d",&r,&c,&t);
    a[i].rows = r;a[i].cols = c;a[i].terms = t;
 }

 transpose(a,b);//b = a transpose
 mmult(a,b,c2);//c2 = a*b
 madd(a,b,d);//d = a+b
 
//resizing c2,d if needed to reduce space wastage
 int s = (c2[0].terms+1);
 if(s<max_terms)
   c2 = realloc(c2,s*sizeof(sparse));
 s = (d[0].terms+1);
 if(s<max_terms)
   d = realloc(d,s*sizeof(sparse));

 print(a,a[0].rows,a[0].cols,"a");
 print(b,b[0].rows,b[0].cols,"b=(a transpose)");
 print(c2,c2[0].rows,c2[0].cols,"c2=(a*b)");
 print(d,d[0].rows,d[0].cols,"d=(a+b)");

 return 0;
}
