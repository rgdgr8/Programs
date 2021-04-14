/*Store the roll and score of the students in a map in the sorted order of roll. One should be able to retrieve the score for a given roll. Take the help of suitable STL class.*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

class student{
   int score;
   string name;
   public:
   student(const string& name,const int score):name(name),score(score){}
   string get_name() const {return name;}
   int get_score() const {return score;}
   friend ostream& operator<<(ostream& o,const student& s) {
      o<<s.name<<" "<<s.score<<endl;
      return o;
   }
};

int main()
{
 map<int,student> m;
 int x = 0;
 do{
   string name;int score;
   cout<<"Enter name: ";
   getline(cin,name);
   cout<<"Enter score: ";
   cin>>score;
   cout<<"Enter roll: ";
   cin>>x;

   if(!m.insert(pair<int,student>(x,student(name,score))).second)
     cout<<"Student with roll "<<x<<" is already present"<<endl;

   cout<<"Enter another? (yes=1,no=0) ";
   cin>>x;
   if(x!=0)
     cin.ignore();
 }while(x>0);

do{
 cout<<"Enter roll to search: ";cin>>x;
 if(m.find(x)!=m.end())
   cout<<"Score for roll "<<x<<" is "<<m.at(x).get_score()<<endl;
 else
   cout<<"Student with roll "<<x<<" not found!"<<endl;
 
 cout<<"Search another? (yes=1,no=0) ";cin>>x;
}while(x>0);

 for(map<int,student>::iterator it = m.begin();it!=m.end();it++)
    cout<<it->first<<" "<<it->second;
}

