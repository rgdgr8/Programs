/*1. There are number of students. For every student roll (unique), name is to be stored. For each subject, subject code and name is to be stored. A student can opt for number of subjects. System should be able to maintain student list, subject list and will be able to answer: i) which student has selected which subjects and ii) for a subjects who are the students.
Design the classes and implement. For list consider memory data structure.*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class student;
class Key;

class subject{
  static int codes;
  int code;
  string name;
  vector<student> students;
  
  public:
  subject(string name):code(codes),name(name){codes++;}
  
  int get_code(){return code;}
  
  string get_name(){return name;}
  
/*Extra key parameter used following the Passkey idiom to restrict access of this function*/
  void add_student(const Key&,student *stu){
    students.push_back(*stu); 
  }
  
  friend ostream& operator<<(ostream& o,const subject& s){
     o<<s.code<<"\t"<<s.name<<endl;
     return o;
  }
  
  vector<student> get_students(){return students;}
  void show_students();
};
int subject::codes = 1;
vector<subject> subjects;

class student{
  static int rolls;
  int roll;
  string name;
  vector<subject> subjects;

  public:
  student(string& name):roll(rolls),name(name){rolls++;}
  
  int get_roll(){return roll;}
  
  string get_name(){return name;}
  
  friend ostream& operator<<(ostream& o,const student& s){
     o<<s.roll<<"\t"<<s.name<<endl;
     return o;
  }
  
  void add_subject();
  
  vector<subject> get_subjects(){return this->subjects;}
  void show_subjects(){
    cout<<"subjects: "<<subjects.size()<<endl;
    for(int i=0;i<this->subjects.size();i++)
       cout<<subjects[i];
  }
};
int student::rolls = 1;
vector<student> students;

void subject::show_students(){
  cout<<"students: "<<subject::students.size()<<endl;
  for(int i=0;i<subject::students.size();i++)
      cout<<subject::students[i];
}

/* Key class for Passkey Idiom */
class Key{
  Key(){} // default ctor private to restrict access to Key
  Key(const Key&){} // copy ctor private to restrict access to Key

  // grant access to add_subject() method of student to create object of Key
  friend void student::add_subject();
};
  
void student::add_subject(){
   while(true){
    cout<<"Enter subject name for Name:"<<this->name<<", Roll:"<<this->roll<<" : ";
    string x;
    getline(cin,x);
    int subs = ::subjects.size();
    subject *sub = nullptr;
    for(int i=0;i<subs;i++)
       if(::subjects[i].get_name()==x)
         sub = &(::subjects[i]);

    if(sub!=nullptr){
      student::subjects.push_back(*sub);
      sub->add_student(Key(),this);
      return;
    }else{
       cout<<x<<" subject is not available"<<endl;
    }
   }
}

//string x[] = {"English","Bengali","Hindi"};
//string y[] = {"rg","sg"};

int main()
{
 int subs = 3,stus = 2;
 cout<<"Enter number of subjects: ";
 cin>>subs;
 cout<<"Enter number of students: ";
 cin>>stus;
 cin.ignore();

 for(int i=0;i<subs;i++){
    // subjects.push_back(subject(x[i]));
   string s;
   cout<<"Enter subject name: ";
   getline(cin,s);  
   subjects.push_back(subject(s));
 }
 for(int i=0;i<stus;i++){
     //students.push_back(student(y[i],100*(i+1)));
     if(i>0)
       cin.ignore();
     string s;
     cout<<"Enter student name: ";
     getline(cin,s);
     students.push_back(student(s));
     int add = 0;
     cout<<"Add subject for "<<s<<"?(yes=1, no=0): ";
     cin>>add;
     while(add==1){
       cin.ignore();
       students[i].add_subject();
       cout<<"Add more subject(s) for "<<s<<"?(yes=1, no=0): ";
       cin>>add;
     }
 }

cout<<"showing subject-wise students:"<<endl;
 for(int i=0;i<subs;i++){
    cout<<subjects[i];
    subjects[i].show_students();
    cout<<"------>>"<<endl;
 } 
 cout<<"----------------------------------"<<endl;
cout<<"showing student-wise subjects:"<<endl;
 for(int i=0;i<stus;i++){
    cout<<students[i];
    students[i].show_subjects();
    cout<<"------>>"<<endl;
 } 
 return 0;
}

