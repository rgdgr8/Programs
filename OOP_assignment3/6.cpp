/*Write a function void f(int) that prints “inside f(int)”. Call the function with actual argument of type: 
i) int, 
ii) char, 
iii) float and 
iv) double. 
Add one more function f(float) that prints “inside f(float)”. Repeat the calls again and observe the outcomes.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void f(int i){
  cout<<"inside f(int)"<<endl;
}
void f(char i){
  cout<<"inside f(char)"<<endl;
}
/*void f(float i){
  cout<<"inside f(float)"<<endl;
}*/
/*void f(double i){
  cout<<"inside f(double)"<<endl;
}*/

int main()
{
 int a = 1;
 char b = 'b';
 float c = 2.0;
 double d = 3.0;
 //f(a);f(b);
 //f(c);//f(d);
 return 0;
}

