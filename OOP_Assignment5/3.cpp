/*3. Employee has unique emp-id, name, designation and basic pay. An employee is either a permanent one or contractual. For permanent employee salary is computed as basic pay+ hra (30% of basic pay) + da (80% of basic pay). For contractual employee it is basic pay + allowance (it is different for different contractual employee). An employee pointer may point to either of the two categories and accordingly the salary has to be created.
Design the classes and implement.*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class employee{
  protected:
  int id;
  string name;
  string des;
  float basic;
  public:
  employee(string name,string des,float basic):name(name),des(des),basic(basic){}
  virtual float salary() = 0;
};

class perm_emp : public employee{
  float hra,da;
  public:
  perm_emp(string name,string des,float basic):employee(name,des,basic){}
  float salary(){ 
    hra = basic*0.3;
    da = basic*0.8;
    return (basic + hra + da);
  }
  float get_hra() const {return hra;}
  float get_da() const {return da;}
};

class temp_emp: public employee{
  float allowance;
  public:
  temp_emp(string name,string des,float basic,float allowance):allowance(allowance),employee(name,des,basic){}
  
  float salary() {return (basic + allowance);}
  float get_allowance() const {return allowance;}
};

int main()
{
 employee *pe = new perm_emp("perm","engg",10000000);
 employee *te = new temp_emp("perm","engg",1000000,150000);

 cout.precision(3);

 cout<<"Permanent employee salary: "<<fixed<<pe->salary()<<endl;
 cout<<"Temporary employee salary: "<<fixed<<te->salary()<<endl;

 return 0;
}

