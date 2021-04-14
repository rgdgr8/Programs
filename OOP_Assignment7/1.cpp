/*Create an array of student objects (containing roll, name, name and score) whose size may vary dynamically once objects are added or removed, randomly elements may be accessed, one can find number of objects in the list, one can find the student with highest score, find the students with a substring in their name and also without a substring in the name. Take the help of suitable STL classes.*/

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

int main()
{
 const string names[] = {"Ganguly","Banerjee","Ganguly","Chakrabarti","Chatterjee"};
 vector<student> students;
 for(int i = 0; i < 5; i++){
     students.push_back(student(names[i],(i+1)));
 }

 vector<student>::iterator it = max_element(students.begin(),students.end(),student::find_max);
 if(it!=students.end())
    cout<<"Max Scorer is: "<<*it;

 vector<student>::iterator start = students.begin();
 while(start!=students.end()){
      start = find_if(start,students.end(),string_matcher("jee",true));
      if(start!=students.end()){
        cout<<*start;
        start++;
      }
 }
}

