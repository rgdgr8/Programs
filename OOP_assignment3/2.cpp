/*Write a function to find the product of two numbers. Call it number of times. Make the functions inline. [check the time of execution and size of object code]*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

inline int product_inline(int a, int b){
 return a*b;
}

int product(int a,int b){
 return a*b;
}  

int main()
{
 int a,b;
 cout<<"Enter two value multiplication: ";
 cin>>a>>b;
 clock_t start = clock();
 int result = product(a,b);
 clock_t end = clock();
 double time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
 cout<<"Time taken by normal func="<<time_taken<<endl;
 cout<<result<<endl;

 start = clock();
 result = product_inline(a,b);
 end = clock();
 time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
 cout<<"Time taken by inline func="<<time_taken<<endl;
 cout<<result<<endl;
 return 0;
}

