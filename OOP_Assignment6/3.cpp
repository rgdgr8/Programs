/*3. Implement a class template for 1D array. Elements may be any basic data type. Provision to find maximum element, sum of the elements must be there.*/

#include <iostream>
using namespace std;

template<class X>
class Array;
template<class X>
ostream& operator<<(ostream&,const Array<X>&);

template<class X>
class Array{
  int size;
  X *arr;
  public:
  Array(int size):size(size){arr = new X[size];}

  int get_size() const {return size;}

  X& operator[] (int i) const {
    if(i<0 || i>size){
      cout <<"Index "<<i<<" is out of bounds"<<endl;
      exit(0);
    }
    return arr[i];
  }

  friend ostream& operator<< <>(ostream& o,const Array<X>& a){
     for(int i=0;i<a.size;i++)
         o<<a[i]<<" ";
     o<<endl;
     return o;
  }

  X max_element() const {
    X max;
    for(int i=0;i<size;i++)
       if(arr[i]>max)
         max = arr[i];
    return max;
  }
  
  X sum_of_elements() const {
     X sum;
     for(int i=0;i<size;i++)
        sum += arr[i];
     return sum;
  }
};

int main()
{
 Array<double> arr(5);
 for(int i=0;i<5;i++)
     arr[i] = i*2.5;
 
 cout<<arr; 
 cout<<"Max: "<<arr.max_element()<<endl;
 cout<<"Sum: "<<arr.sum_of_elements()<<endl;
}

