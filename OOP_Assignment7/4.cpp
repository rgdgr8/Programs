/*Maintain a container of students where they are kept in the descending order of their scores. Take the help of suitable STL class.*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

class student{
   static int rolls;
   int roll;
   string name;
   public:
   student(const string& name):name(name),roll(rolls){rolls++;}
   friend ostream& operator<<(ostream& o,const student& s) {
      o<<s.roll<<" "<<s.name;
      return o;
   }
};
int student::rolls = 1;

int main()
{
 multimap<int,student,greater<int> > m;//multimap used to store duplicate score as keys as well
 int x = 0;
 do{
   string name;
   cout<<"Enter name: ";
   getline(cin,name);
   cout<<"Enter score: ";
   cin>>x;
   m.insert(pair<int,student>(x,student(name)));
   cout<<"Enter another? (yes=1,no=0) ";
   cin>>x;
   if(x!=0)
     cin.ignore();
 }while(x>0);

 for(multimap<int,student,greater<int> >::iterator it = m.begin();it!=m.end();it++)
    cout<<it->second<<" "<<it->first<<endl;
}

