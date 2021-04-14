#include <iostream> 
using namespace std;

template<class x>
class X{
  public:
  X(){y++;}
  static int y;
};
template<class Y>
int X<Y>::y = 0;

int main() {
  X<int> a[3];
  cout<<X<int>::y<<endl;
  cout<<X<float>::y<<endl;
  X<float> b[4]; 
  cout<<X<int>::y<<endl;
  cout<<X<float>::y<<endl;
}
