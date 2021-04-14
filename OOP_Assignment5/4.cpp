/*4. Each cricketer has name, date of birth and matches played. Cricketer may be a bowler or batsman. For a bowler, number of wickets taken, average economy is stored. For a batsman, total runs scored, average score is stored. A double wicket pair is formed taking a bowler and a batsman. An all-rounder is both a bowler and batsman. Support must be there to show the details of a cricketer, bowler, batsmen, all-rounder and the pair.
Design the classes and implement.*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class cricketer{
  protected:
  string name;
  string dob;
  int matches;
  void print_basic_details() const {
     cout<<"Name: "<<name<<endl;;
     cout<<"DOB: "<<dob<<endl;;
     cout<<"Total matches played: "<<matches<<endl;;
  }
  public:
  cricketer(string name,string dob,int matches):name(name),dob(dob),matches(matches)
  {/*cout<<"cricketer"<<endl;*/}
  string get_name() const {return name;}
  string get_dob() const {return dob;}
  int get_matches() const {return matches;}
  void set_matches(int m) {matches = m;}
  virtual void print_details() const = 0;
};

class batsman: virtual public cricketer{
  int runs;
  float avg;
  public:
  batsman(string name,string dob,int matches,int runs,float avg):cricketer(name,dob,matches),runs(runs),avg(avg){/*cout<<"batsman"<<endl;*/}
  
  int get_runs() const {return runs;}
  float get_avg_score() const {return avg;}
  void set_runs(int r) {runs = r;}
  void set_avg_score(float a) {avg = a;}
  
  void print_details() const{
     print_basic_details();
     cout<<"Batting:"<<endl;
     cout<<"Runs: "<<runs<<endl;
     cout<<"Average score: "<<avg<<endl;
     cout<<"----------------------"<<endl;
  }
};

class bowler: virtual public cricketer{
  int wickets;
  float avg;
  public:
  bowler(string name,string dob,int matches,int wickets,float avg):cricketer(name,dob,matches),wickets(wickets),avg(avg){/*cout<<"bowler"<<endl;*/}
  
  int get_wickets() const {return wickets;}
  float get_avg_economy() const {return avg;}
  void set_wickets(int w) {wickets = w;}
  void set_avg_economy(float a) {avg = a;}
  
  void print_details() const{
     print_basic_details();
     cout<<"Bowling:"<<endl;
     cout<<"Wickets taken: "<<wickets<<endl;
     cout<<"Average economy: "<<avg<<endl;
     cout<<"----------------------"<<endl;
  }
};

class all_rounder : public batsman,public bowler{
  public:
  all_rounder(string name,string dob,int matches,int runs,float avg_sc,int wickets,float avg_ec):batsman(name,dob,matches,runs,avg_sc),bowler(name,dob,matches,wickets,avg_ec),cricketer(name,dob,matches){/*cout<<"all_rounder"<<endl;*/}
  void print_details() const{
    cout<<"All Rounder"<<endl;
    batsman::print_details();
    bowler::print_details();
    cout<<"----------------------"<<endl;
  }
};

class dw_pair{
  batsman *bat;
  bowler *bowl;
  public:
  dw_pair(string name1,string dob1,int matches1,string name2,string dob2,int matches2,int runs,float avg_sc,int wickets,float avg_ec){
    //cout<<"dw_pair"<<endl;
    bat = new batsman(name1,dob1,matches1,runs,avg_sc);
    bowl = new bowler(name2,dob2,matches2,wickets,avg_ec);
  }
  
  int get_runs() const {return bat->get_runs();}
  float get_avg_score() const {return bat->get_avg_score();}
  void set_runs(int r) {bat->set_runs(r);}
  void set_avg_score(float a) {bat->set_avg_score(a);}
 
  int get_wickets() const {return bowl->get_wickets();}
  float get_avg_economy() const {return bowl->get_avg_economy();}
  void set_wickets(int w) {bowl->set_wickets(w);}
  void set_avg_economy(float a) {bowl->set_avg_economy(a);}

  void print_details() const{
     cout<<"Double Wicket Pair"<<endl;
     bat->print_details();
     bowl->print_details();
  }

  ~dw_pair(){delete bat; delete bowl;}
};

int main()
{
 batsman bat("bat1","1/1/1",100,100,50.5);
 bowler bowl("bowl1","2/2/2",90,90,40.5);
 all_rounder ar("AR","3/3/3",110,110,50,30,15);
 dw_pair dw("Dw1","4/4/4",13,"Dw2","5/5/5",15,10,5.3,4,150);
 
 bat.print_details();
 bowl.print_details();
 ar.print_details();
 dw.print_details();
 return 0;
}

