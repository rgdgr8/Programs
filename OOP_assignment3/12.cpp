/*Design a STUDENT class to store roll, name, course, admission date and marks in 5 subjects. Provide methods corresponding to admission (marks are not available then), receiving marks and preparing mark sheet. Support must be there to show the number of students who have taken admission.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int subs = 5;
const string subjects[5] = {"Maths","OOP","DSA","COA","Digital Logic"};

class student{
  static int num;
  string name;
  float scores[subs];
  int roll;
  string course;
  string date;
  void marksheet(){
   cout<<"Date of admission: "<<date<<endl;
   cout<<"Roll: "<<roll<<endl<<"Name: "<<name<<endl<<"Course: "<<course<<endl;
   for(int i=0;i<subs;i++)
      cout<<subjects[i]<<" - "<<scores[i]<<endl;
  }
  public:
  void admit(const string &name,const string& course,const string& date){
   this->name = move(name);
   num++;
   roll = num;
   this->course = move(course);
   this->date = move(date);
  }
  void give_marks(){
    cout<<name<<"'s "<<"scores:"<<endl;
    for(int i=0;i<subs;i++){
       cout<<"Enter marks for "<<subjects[i]<<": ";
       cin>>scores[i];
    }
    marksheet();
  }
  static void number_of_students(){cout<<"Number of students is: "<<num<<endl;}
};

int student::num = 0;

int main()
{
 student a,b;
 a.admit("Rahul Maiti","CSE","22/12/23");
 a.give_marks();
 student::number_of_students();
 b.admit("Rishav paul","IEE","20/10/23");
 b.give_marks();
 student::number_of_students();
 
 return 0;
}

