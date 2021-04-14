/*Design an ARRAY class with the following features:
a. Array object may be declared for a specific size and a value for initializing
all the elements. If this it is to be assumed as a 0.
b. An array object may be declared and initialized with another object.
c. An array object may be declared and initialized with another array (not
the object, standard array as in C language).
Let a and b are two objects:
i. a+b will add corresponding elements.
ii. a=b will do the assignment.
iii. a[I] will return the ith element of the object. iv. a*5 or 5*a will multiply the element with 5.*/

#include <iostream>
#include <cassert>
using namespace std;

template<class T>
class ARRAY{
  T* ptr;
  public:
  const int size;
  ARRAY(int size,int val = 0):size(size){assert(size>0);ptr = new T[size];for(int i=0;i<size;i++)ptr[i]=val;}
  ARRAY(T* const arr,int size):size(size){assert(size>0);ptr = new T[size];for(int i=0;i<size;i++)ptr[i]=arr[i];}
  ARRAY(const ARRAY<T>& arr):size(arr.size){
  // cout<<"Copy cst"<<endl;
   assert(size>0);ptr = new T[size];for(int i=0;i<size;i++)ptr[i]=arr.ptr[i];
  }
  ARRAY(ARRAY<T>&& arr):size(arr.size){
//    cout<<"Move cst"<<endl;
    ptr = move(arr.ptr);
    arr.ptr = nullptr;
  }
  T& operator[](int i) const{
    assert(i<size && i>=0);    
    return ptr[i];
  }
  ARRAY<T> operator+(const ARRAY<T>& arr){
     T* p = new T[arr.size];
     for(int i=0;i<arr.size;i++)
        p[i] = (this->ptr[i])+(arr[i]);
     ARRAY<T> x(p,arr.size);
     return x;
  }
  void operator=(const ARRAY<T>& arr){
     assert(this->size>=arr.size);
     for(int i=0;i<arr.size;i++)
        (this->ptr[i]) = (arr[i]);
  }
  template<class T2>
  friend void operator*(T2 x,const ARRAY<T>& arr){
    for(int i=0;i<arr.size;i++)
        arr[i] = 5*arr[i];
  }
  template<class T2>
  friend void operator*(const ARRAY<T>& arr,T2 x){
     x*arr;
  }
  friend ostream& operator<<(ostream& o,const ARRAY<T>& arr){
      for(int i=0;i<arr.size;i++)
         cout<<arr[i]<<" ";
     return o;
  }
  ~ARRAY(){if(ptr) delete []ptr;}
};

int main()
{
 ARRAY<int> a(10,5);
 cout<<"a= "<<a<<endl;
 ARRAY<int> b(a);
 cout<<"b=a= "<<b<<endl;
 ARRAY<int> d = a+b;
 cout<<"d=a+b= "<<d<<endl;
 a*5;
 ARRAY<int> c = a;
 cout<<"c=a*5= "<<c<<endl;
 return 0;
}

