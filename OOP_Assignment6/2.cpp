/*
2. Consider a class Student with roll, name and score as attributes. Support to take and display data is also there. One wants to works with array of Student objects. May collect data for array elements, display those. In case index goes out of bounds, exception is to be raised with suitable message.*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;
int size;

class student{
  static int rolls;
  int roll;
  string name;
  int score;
  public:
  student():roll(-1),name(""),score(-1){}
  void input(string n,int s){name=n;score=s;roll=rolls;rolls++;}
  friend ostream& operator<<(ostream& o,const student& s){
    if(s.roll!=-1)
      o<<"Roll: "<<s.roll<<" "<<"Name: "<<s.name<<" "<<"Score: "<<s.score<<endl;
    return o;
  }
};
int student::rolls = 1;

void input(student* stu) throw(const char*){
   int s;
   cout<<"Enter number of students to enter: ";
   cin>>s;
   if(s>size)
     throw "Access out of bounds for input";
   
   for(int i=0;i<s;i++)
      stu[i].input("name"+to_string(i),(90+i));
}

void display_all(student* stu) throw() {
    for(int i=0;i<size;i++)
        cout<<stu[i];
}

int main() {
  cout<<"Enter size: ";
  cin>>size;
  student students[size];
  try{
    input(students);
  }catch(const char* s){
    cout<<s<<endl;
  }
  display_all(students);
}

