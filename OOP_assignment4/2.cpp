/*Design a COMPLEX class, which will behave like normal integer with respect to
addition,
subtraction,
accepting the value and Displaying the value.*/

#include <iostream>
using namespace std;

template<class T>
class COMPLEX{
  T real;
  T img;
  public:
  COMPLEX(){}
  COMPLEX(T r,T i=0):real(r),img(i){}
  friend ostream& operator<<(ostream& o,const COMPLEX<T>& c){
    o<<c.real<<"+i("<<c.img<<")";
    return o;
  }
  friend istream& operator>>(istream& i,COMPLEX<T>& c){
    cout<<"Real part: ";
    i>>c.real;
    cout<<"Imaginary part: ";
    i>>c.img;
    return i;
  }
  friend COMPLEX<T> operator+(const COMPLEX<T>& a,const COMPLEX<T>& b){
     COMPLEX<T> c((a.real+b.real),(a.img+b.img));
     return (c);
  }
  friend COMPLEX<T> operator-(const COMPLEX<T>& a,const COMPLEX<T>& b){
     COMPLEX<T> c((a.real-b.real),(a.img-b.img));
     return (c);
  }
};


int main()
{
 COMPLEX<double> a(1.2,2.3),b;
 cin>>b;
 COMPLEX<double> c = a-COMPLEX<double>(1.3);
 cout<<c<<endl;
 c = a+b;
 cout<<c<<endl;
 return 0;
}

