/*Write a function swap (a, b) to interchange the values of two variables. Do not use pointers.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

template<class T>
void my_swap(T& a,T& b){
  T t = move(a);
  a = move(b);
  b = move(t);
}

int main()
{
 vector<int> a(10),b(10);
 for(int i=0;i<10;i++){
     a[i] = i;
     b[i] = i+100;
 }
 cout<<"Before my_swap: "<<endl;
 for(int i=0;i<10;i++)
     cout<<a[i]<<" ";
 cout<<endl;
 for(int i=0;i<10;i++)
     cout<<b[i]<<" ";
 cout<<endl;

 my_swap(a,b);
 cout<<"After my_swap: "<<endl;
 for(int i=0;i<10;i++)
     cout<<a[i]<<" ";
 cout<<endl;
 for(int i=0;i<10;i++)
     cout<<b[i]<<" ";
 cout<<endl;
 return 0;
}

