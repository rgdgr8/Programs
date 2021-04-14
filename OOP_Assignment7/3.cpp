/*Students come to mark sheet collection desk and are served in first come first served basis. Implement the scenario. Take the help of suitable STL class.*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class marksheet{
   static int rolls;
   int roll;
   string name;
   int score;
   public:
   marksheet(const string& name,const int score):roll(rolls),name(name),score(score){rolls++;}
   friend ostream& operator<<(ostream& o,const marksheet& m){
       o<<m.roll<<" "<<m.name<<" "<<m.score<<endl;
       return o;
   }
   bool operator==(const int r) const {return roll==r;}
};
int marksheet::rolls = 1;

int main()
{
 
 vector<marksheet> marksheets;
 for(int i=0;i<100;i++)//filling marksheets upto 100 rolls
    marksheets.push_back(marksheet("name"+to_string((i+1)),(i+1)));

 queue<int> q;
 int x;
 do{
   cout<<"Enter roll (enter 0 to cancel): ";
   cin>>x;
   if(x>100 || x<0){//max roll 100 (programmer decided)
     cout<<"Enter a valid roll"<<endl;
     continue;
   }
   if(x!=0)
     q.push(x);
 }while(x>0);

 while(!q.empty()){
    vector<marksheet>::iterator it = find(marksheets.begin(),marksheets.end(),q.front());
    q.pop();
    if(it!=marksheets.end())
      cout<<*it;
    else
      cout<<"Marksheet Not Found!"<<endl;
 }
}

