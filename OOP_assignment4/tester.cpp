#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int a[] = {1,2,3};

class X{
  int x;
  public:
  friend X xx();
  int get_x(){return x;}
  void xxx(){
    for(int i=0;i<3;i++)
       cout<<a[i]<<endl;
  }
};
  
X xx(){
    X t;
    t.x = 111;
    return t;
}

void inp(string& s){
  getline(cin,s);
}
void inp2(){
  cout<<"ola:"<<endl;
  string s;
  getline(cin,s);
  cout<<s<<endl;
}

int main(){
 int x;
 string s = "null";
 cin>>x;
 //cin>>s;
 //getline(cin,s);
 //inp(s);
 inp2();
 cout<<x<<" "<<s<<endl;
 return 0;
}
