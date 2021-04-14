/*Design a STRING class, which will have the initialization facility similar to array class. Provide support for
• Assigning one object for another,
• Two string can be concatenated using + operator,
• Two strings can be compared using the relational operators.*/

#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

class STRING{
  private:
  char* s;
  int size;
  public:
  STRING(char* const c):size(strlen(c)){assert(size>0);s=new char[size+1];strcpy(s,c);}
  STRING(const char* const c):size(strlen(c)){assert(size>0);s=new char[size+1];strcpy(s,c);}
  STRING(const STRING& x):size(x.get_size()){assert(size>0);s=new char[size+1];strcpy(s,x.s);}
  friend ostream& operator<<(ostream& o,const STRING& s) {
     o<<s.s;
     return o;
  }
  int get_size() const {return size;}
  int operator==(const STRING& x){
     if(x.get_size()!=size)
       return 0;
     
     return strcmp(s,x.s);
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
      size = x.size;
      delete s;
      s = new char[size+1];
      strcpy(s,x.s);
  }
  ~STRING(){if(s) delete []s;}
};

int main()
{
 char *a = new char[5];
 strcpy(a,"kola");
 STRING x(a);
 cout<<"x="<<endl;
 cout<<x<<endl;
 cout<<x.get_size()<<endl;
 
 STRING c = x+"ola"; 
 cout<<"c="<<endl;
 cout<<c<<endl;
 cout<<c.get_size()<<endl;
 
 cout<<(c=="kolaol")<<endl;

 STRING *y = new STRING(x);
 cout<<"y="<<endl;
 cout<<*y<<endl;
 cout<<y->get_size()<<endl;
 delete y;
 return 0;
}

