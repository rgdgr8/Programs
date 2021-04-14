/*Write a macro to find the maximum of two numbers. 
Call the macro with 
i) two integers as the arguments and 
ii) two char * as the arguments. Observe the outcomes.*/

#include<iostream>
#include<cstdlib>
#include<string>
#define max(a,b) a==b ? a : (a<b ? b : a)

using namespace std;

int main()
{
 int a,b;
 string s1,s2;
 cout<<"Enter two values: ";
 cin>>a>>b;
 cout<<"Enter two strings : ";
 cin>>s1>>s2;
 cout<< (max(a,b)) <<" is greater or equal"<<endl;
 cout<<(max(s1,s2))<<" is greater or equal"<<endl;
 return 0;
}
