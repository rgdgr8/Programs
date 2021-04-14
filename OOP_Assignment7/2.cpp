/*Create an array of student objects where along with the support mentioned in Q.1, one can remove an object with specific roll, sort the collection in the descending order and show the same; two student collections can also be combined. Take the help of suitable STL class.*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class student{
  static int rolls;
  int roll;
  string name;
  int score;
  public:
  student(const string& name,const int score):name(name),score(score),roll(rolls){rolls++;}
  int get_score() const {return score;}
  string get_name() const {return name;}
  int get_roll() const {return roll;}
  void set_score(int x) {score = x;}
  static bool find_max(const student& a,const student& b){return a.score<b.score;}
  friend ostream& operator<<(ostream& o,const student& s){
    o<<s.roll<<" "<<s.name<<" "<<s.score<<endl;
    return o;
  }
};
int student::rolls = 1;

class string_matcher{
   const string pattern;
   const bool with;//boolean indicating if name with pattern is to be found or without the pattern
   public:
   string_matcher(const string& pattern,bool with):pattern(pattern),with(with){}
   bool operator()(const student& stu) const {
      string name = stu.get_name();
      if(name.size()<pattern.size())
         return !with;
      int i = 0;
      while(i <= name.size()-pattern.size()){
         int flag = 1;
         for(int j = 0; j < pattern.size(); j++){
            if(name.at(i) != pattern.at(j)){
              flag = 0;
              if(j==0)
                 i++;
              break;
            }
            i++;
         }
         if(flag)
            return with;
      }
      return !with;
   }
};

class remove_by_roll{
   int roll;
   public:
   remove_by_roll(int roll):roll(roll){}
   bool operator()(const student& s) const {
      return roll==s.get_roll();
   }
};

class sort_desc_by{
   int choice;
   public:
   sort_desc_by(int c):choice(c){}
   bool operator()(const student& a,const student& b) const {
      switch(choice){
         case 1: return a.get_roll()>b.get_roll();
         case 2: return a.get_name()>b.get_name();
         case 3: return a.get_score()>b.get_score();
         default : cout<<"Invalid input to sort_desc_by"<<endl;exit(0);
      }
   }
};

void print_students(const vector<student>& x){
   vector<student>::const_iterator i = x.cbegin();
   for(;i!=x.cend();i++)
      cout<<*i;
}

int main()
{
 const string names[] = {"Ganguly","Banerjee","Ganguly","Chakrabarti","Pal"};
 vector<student> students;
 for(int i = 0; i < 5; i++){
     students.push_back(student(names[i],(i+1)));
 }
 print_students(students);
 cout<<"-------------------------"<<endl;

 vector<student>::iterator it = max_element(students.begin(),students.end(),student::find_max);
 if(it!=students.end())
    cout<<"Max Scorer is: "<<*it;
 cout<<"-------------------------"<<endl;

 vector<student>::iterator start = students.begin();
 while(start!=students.end()){
      start = find_if(start,students.end(),string_matcher("Ganguly",false));
      if(start!=students.end()){
        cout<<*start;
        start++;
      }
 }
 cout<<"-------------------------"<<endl;
 sort(students.begin(),students.end(),sort_desc_by(2));
 print_students(students);
 cout<<"-------------------------"<<endl;

 vector<student> students2;
 for(int i = 0; i < 5; i++){
     students2.push_back(student("name"+to_string((i+1)),(i+1)));
 }
 print_students(students2);
 cout<<"-------------------------"<<endl;
 
 vector<student> students3;
 for(int i=0;i<students.size();i++)
     students3.push_back(students[i]);
 for(int i=0;i<students2.size();i++)
     students3.push_back(students2[i]);
 print_students(students3);
 cout<<"sizeof students3: "<<students3.size()<<endl;
 cout<<"-------------------------"<<endl;
 cout<<"Input roll to delete: ";int x;
 cin>>x;
 it = remove_if(students3.begin(),students3.end(),remove_by_roll(x));//logical deletion
 if(it!=students3.end()){//actual deletion
       students3.erase(it,students3.end());
 }

 cout<<"sizeof students3: "<<students3.size()<<endl;
 print_students(students3);
}

