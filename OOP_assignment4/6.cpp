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
  vector<student*> students;
  
  public:
  subject(string name):code(codes),name(name){codes++;}
  
  int get_code(){return code;}
  
  string get_name(){return name;}
  
/*Extra key parameter used following the Passkey idiom to restrict access of this function*/
  void add_student(const Key&,student *stu){students.push_back(stu);}
  
  friend ostream& operator<<(ostream& o,const subject& s){
     o<<s.code<<"\t"<<s.name<<endl;
     return o;
  }
  
  vector<student*> get_students(){return students;}
  void show_students();
};
int subject::codes = 1;
vector<subject> subjects;

class student{
  static int rolls;
  int roll;
  string name;
  int number;
  vector<subject*> subjects;

  public:
  student(string& name,int number):roll(rolls),name(name),number(number){rolls++;}
  
  int get_roll(){return roll;}
  
  int get_number(){return number;}
  
  string get_name(){return name;}
  
  void set_number(int newNumber){number=newNumber;}

  friend ostream& operator<<(ostream& o,const student& s){
     o<<s.roll<<"\t"<<s.name<<endl;
     return o;
  }
  
  void add_subject(int); //this uses global subejects vector
  
  vector<subject*> get_subjects(){return this->subjects;}
  void show_subjects(){for(int i=0;i<this->subjects.size();i++)cout<<*subjects[i];}
};
int student::rolls = 1;
vector<student> students;

void subject::show_students(){for(int i=0;i<students.size();i++)cout<<*students[i];}

/* Key class for Passkey Idiom to restrict access to subject::add_student()*/
class Key{
  Key(){} // default ctor private to restrict access to Key
  Key(const Key&){} // copy ctor private to restrict access to Key

  // grant access to add_subject() method of student to create object of Key
  friend void student::add_subject(int);
};
  
void student::add_subject(int subs){
    cout<<"Enter subject name for Name:"<<this->name<<", Roll:"<<this->roll<<" : ";
    string x;
    getline(cin,x);
    subject *sub = nullptr;
    for(int i=0;i<subs;i++)
       if(::subjects[i].get_name()==x)
         sub = &(::subjects[i]);
  
    if(sub!=nullptr){
      subjects.push_back(sub);
      sub->add_student(Key(),this);
    }else{
       cout<<x<<" subject is not available"<<endl;
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
     string s;
     cout<<"Enter student name: ";
     getline(cin,s);
     int x;
     cout<<"Enter student number: ";
     cin>>x;
     cin.ignore();
     students.push_back(student(s,x));
     for(int j=0;j<=i;j++)
       students[i].add_subject(subs);
 }

 for(int i=0;i<subs;i++){
    cout<<subjects[i];
    subjects[i].show_students();
 } 
 cout<<"----------------------------------"<<endl;
 for(int i=0;i<stus;i++){
    cout<<students[i];
    students[i].show_subjects();
 } 
 return 0;
}

