/*Define functions f(int, int) and f (char, int). Call the functions with arguments of type (int, char), (char,char) and (float, float).*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void f(int x,int y){
 cout<<"inside f(int,int)"<<endl;
}
void f(char x,int y){
 cout<<"inside f(char,int)"<<endl;
}

int main()
{
 int a = 1;
 char b = 'b';
 float c = 2.0;
 f(a,b);f(b,b);//f(c,c);
 return 0;
}

