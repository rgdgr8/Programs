/*Create an APPLICANT class with application id (auto generated as last id +1), name and score. Support must be there to receive applicant data, show applicant details and to find out number of applicants.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class applicants{
  static int num_of_app;
  string name;
  int score;
  int roll;
  public:
  void admit(const string &name,const int &score){
   this->name = move(name); this->score = score;
   num_of_app++;
   roll = num_of_app;
  }
  void show(){cout<<"Roll: "<<roll<<endl<<"Name: "<<name<<endl<<"Score: "<<score<<endl;}
  static void number_of_applicants(){cout<<"Number of applicants is: "<<num_of_app<<endl;}
};

int applicants::num_of_app = 0;

int main()
{
 applicants a,b;
 a.admit("Rahul Maiti",100);
 a.show();
 applicants::number_of_applicants();
 b.admit("Rishav paul",90);
 b.show();
 applicants::number_of_applicants();
 
 return 0;
}

