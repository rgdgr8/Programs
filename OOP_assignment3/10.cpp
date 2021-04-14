/*Create a STACK class with operation for initialization, push and pop. Support for checking underflow and overflow condition are also to be provided.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class stack{
  int* arr;
  int size;
  int max;
  public:
  stack(int max_size): arr(new int[max_size]),size(0),max(max_size){}
  void show(){
    cout<<"Stack is:"<<endl;;
    for(int i=size-1;i>=0;i--)
       cout<<arr[i]<<endl;
    cout<<endl;
  }
  void push(int v){
   if(size<max)
      arr[size++] = v;
   else
     cout<<"Stack is already full"<<endl;
  }
  void pop(){
   if(size>0)
     size--;
   else
     cout<<"Stack is already empty"<<endl;
  }
  bool is_empty(){ 
    return (!size);
  }
  int curr_size(){
    return size;
  }
};

int main()
{
 stack s(5);
 cout<<s.is_empty()<<endl;
 cout<<s.curr_size()<<endl;
 for(int i=0;i<6;i++){
    s.push(i+12);
 }
 s.show();
 s.pop();
 cout<<s.is_empty()<<endl;
 cout<<s.curr_size()<<endl;
 s.show();
 for(int i=0;i<5;i++)
    s.pop();
 s.show();
 s.push(100);
 cout<<s.is_empty()<<endl;
 cout<<s.curr_size()<<endl;
 s.show();
 return 0;
}

