/*Define a structure student with roll and score as attributes and with two member functions to take input and to show the data. Use the member functions to take data for a structure variable and to show. Write global function i) to modify score and ii) to show the data again.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct student{
  int roll;
  float score;
  void input(){
    cout<<"Enter roll: ";
    int roll;cin>>roll;
    cout<<"Enter score: ";
    int score;cin>>score;
    this->roll = roll;
    this->score = score;
  }
  void show(){
    cout<<"Roll: "<<roll<<endl<<"Score: "<<score<<endl;
  }
}s;

void modify(student &x,int score = s.score,int roll = s.roll){
  x.roll = roll;
  x.score = score;
  x.show();
}

int main()
{
 s.input();
 s.show();
 modify(s,10);
 return 0;
}

