#include<stdio.h>
#include<stdlib.h>
#include<tgmath.h>
#include<string.h>
#define prime 1009
 
int temp_index = 0;
void fill_temp(int temp[], int num){//helper function to fill up temp array in reverse of num
 temp_index = 0;
// printf("temp = ");
 while(num>0){
    int d = num%10;
  //  printf("%d-",d);
    temp[temp_index++] = d;
    num/=10;
 }
// printf("\ntemp_index = %d\n",temp_index);
}
 
void print(int a[],int size){//print number
 int begin = 0;
 if(a[0]==0)
   begin = 1;
 for(int i=begin;i<size;i++)
    printf("%d",a[i]);
 printf("\n");
}
 
void add(int a[], int b[], int size,int c[]);//addition on the numbers stored digit by digit in arrays

void divide(int s[],int size){//division on the numbers stored digit by digit in arrays
 int begin = 0;
 if(s[0]==0)
   begin = 1;
 int dividend = 0;
 while(begin<size){
 //     printf("\nbegin = %d & s[%d] = %d & dividend = %d\n",begin,begin,s[begin],dividend);
      dividend = dividend*10+s[begin];
   //   printf("dividend = %d\n",dividend);
      if(dividend>=prime)
        dividend = dividend % prime;
      begin++;
 }
 printf("%d\n",dividend);   
}

int main()
{
 char* c = malloc(100);
 printf("Enter a name for converion to number: ");
 scanf("%[^\n]%*c", c);
 int size = strlen(c);
 int nums[3*size];
 int j = 0; 
 for(int i=0;i<size;i++){
    int num = *(c+i);
  //  printf("num = %d\n",num);
    if(num!=32){//if char is not a space
     int temp_size = 2;//digits in ascii value may be 2
     if(num>99)//if more than 99
       temp_size = 3;//digits in ascii value is 3
       int temp[temp_size];
       fill_temp(temp,num);//stores digits of num in temp array
       while(temp_index>0){
    //     printf("j = %d & temp_index = %d\n",j,temp_index);
           nums[j++] = temp[--temp_index];//store from temp to nums in reverse
      //   printf("nums[%d] = %d\n",j-1,nums[j-1]);
      }
    }   
 }
 int half1_size = j/2;//actual size of half1
 int half2_size = j - half1_size;
 int half1[half2_size];//half2_size used for uniformity
 int half2[half2_size];
 int diff = half2_size - half1_size;
 for(int x = 0;x<half2_size;x++){//fill half1 with first half of nums
    if(x<diff)
      half1[x] = 0;//fill the front with 0s if half1_size is less than half2_size
    else
      half1[x] = nums[x-diff];
 }
 for(int y = 0;y<half2_size;y++)//fill half2 with second half of nums
    half2[y] = nums[half1_size + y];
 int sum[(half2_size+1)];
 add(half1,half2,half2_size,sum);
 printf("name-->number = ");
 print(nums,j);
 printf("\nfirst half = ");
 print(half1,half2_size);
 printf("\nsecond half = ");
 print(half2,half2_size);
 printf("\nsum = ");
 print(sum,(half2_size+1));
 printf("\nRequired remainder = ");
 divide(sum,(half2_size+1));
 return 0;
}

void add(int a[], int b[], int size, int c[])
{
 int carry = 0;
 for(int i = size-1;i>=0;i--){
    int sum = a[i] + b[i] + carry;
    if(sum<10){
      c[i+1] = sum;
      carry = 0;
    }
    else{
      c[i+1] = sum%10; 
      carry = 1;
    }
 }
 c[0] = carry;
}
