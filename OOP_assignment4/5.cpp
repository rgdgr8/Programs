/*Modify the STRING class so that assigning/initializing a string by another will not copy it physically but will keep a reference count, which will be incremented. Reference value 0 means the space can be released.*/

#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

class STRING{
  private:
  char* s;
  int *count;
  int size;
  public:
  STRING(char* const c):size(strlen(c)),count(new int(1)){assert(size>0);s=new char[size+1];strcpy(s,c);}
  STRING(const char* const c):size(strlen(c)),count(new int(1)){assert(size>0);s=new char[size+1];strcpy(s,c);}
  STRING(const STRING& x):size(x.get_size()),count(x.count){assert(size>0);s=x.s;(*count)++;}
  friend ostream& operator<<(ostream& o,const STRING& s) {
     o<<s.s;
     return o;
  }
  int get_size() const {return size;}
  int operator==(const STRING& x){
     if(x.get_size()!=size)
       return 0;
     
     for(int i=0;i<size;i++)
        if(x.s[i]!=s[i])
          return 0;
     return 1;
  }
  friend STRING operator+(const STRING& a,const STRING& b){
      //cout<<"+: "<<a<<" "<<b<<endl;
      int sizet = a.get_size()+b.get_size();
      //cout<<"sizet="<<sizet<<endl;
      char *st = new char[sizet+1];
      int i;
      for(i=0;i<(a.get_size());i++)
         st[i] = a.s[i];
      for(int j=0;j<(b.get_size());j++)
         st[i++] = b.s[j];
     st[i] = '\0';
     //cout<<"Final copy st: "<<st<<endl;
     STRING x(st);
     return x;
  }
  void operator=(STRING& x){
    if(x.s==s)return;

    (*count)--;
    if(*count<=0) {delete []s;delete count;}
    s = x.s;
    count = x.count;
    size = x.get_size();
    (*count)++;
  }
  int ptr_count(){return *count;}
  ~STRING(){if(*count<=1) {/*cout<<"deleted: "<<s<<endl;*/delete count;delete []s;}/*else cout<<"undeleted: "<<s<<endl;*/}
};

int main()
{
 char *a = new char[5];
 strcpy(a,"kola");
 STRING x(a);
 cout<<"x : "<<endl; 
 cout<<x<<endl;
 cout<<"size="<<x.get_size()<<endl;
 cout<<"ptr_count="<<x.ptr_count()<<endl;
 cout<<"After STRING z = x : ";
 STRING z = x;
 cout<<"ptr_count="<<x.ptr_count()<<endl;

 STRING c = x+"ola"; 
 cout<<"c : "<<endl; 
 cout<<c<<endl;
 cout<<"size="<<c.get_size()<<endl;
 cout<<"ptr_count="<<x.ptr_count()<<endl;
 
 cout<<"c== \"kolaol\" ? "<<(c=="kolaol")<<endl;

 STRING *y = new STRING(x);
 cout<<"y : "<<endl; 
 cout<<*y<<endl;
 cout<<"size="<<y->get_size()<<endl;
 cout<<"ptr_count="<<x.ptr_count()<<endl;
 delete y;
 return 0;
}

