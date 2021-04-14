/*Write a function max (a, b) that will return the reference of larger value. Store the returned information to x where x is a 
i) variable of type a or b, 
ii) variable referring to type of a or b. In both the cases modify x. Check also the values of a and b.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

template<class T>
inline T& my_max(T& a,T& b){
  if(a==b)
    return a;
  else
    if(a>b)
      return a;
    else
      return b;
}

int main()
{
 int a = 1, b = 2;
 int x = my_max<int>(a,b);
 cout<<"Same type:"<<endl;
 cout<<"x="<<x<<endl;
 x+= 10;
// cout<<"x+=10 ="<<x<<endl;
 cout<<"a="<<a<<" b="<<b<<endl;
 int &y = my_max<int>(a,b);
 cout<<"Refrence type:"<<endl;
 cout<<"y="<<y<<endl;
 y+=10;
// cout<<"y+=10 ="<<y<<endl;
 cout<<"a="<<a<<" b="<<b<<endl;
 
 return 0;
}

