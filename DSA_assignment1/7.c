#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PRIME1 1009
#define PRIME2 1129
#define MOD 100000
#define ADD 100000000

int main()
{
 for(int i=0;i<10;i++){
 unsigned long x = rand()%MOD + ADD;
 unsigned long r = x%PRIME1; 
 printf("%lu\t%lu\n",x,r);
 }
 return 0;
}
