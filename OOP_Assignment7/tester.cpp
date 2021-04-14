#include <iostream>
#include <string>
#include <map>
using namespace std;

class x{
  public:
  string s;
  //x(){cout<<"default"<<endl;}
  x(string s=""):s(s){cout<<"mine"<<endl;}
};

int main()
{
  map<int,x> m;
  m.insert(pair<int,x>(1,x("me")));
  cout<<m[1].s<<endl;
}

