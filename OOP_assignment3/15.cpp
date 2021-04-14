/*Design a BALANCE class with account number, balance and date of last update. Consider a TRANSACTION class with account number, date of transaction, amount and transaction type (W for withdrawal and D for deposit). If it is a withdrawal check whether the amount is available or not. Transaction object will make necessary update in the BALANCE class.*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum type{W,D,I};
ostream& operator<<(ostream& o,const type& t){
  if(t==0)
    o<<"Withdrawal";
  else if(t==1)
    o<<"Deposit";
  else
    o<<"Incomplete";
  return o;
}

class balance{
  string last_upd;
  int acc;
  float bal;
  public:
  balance(int acc,const string& d,int bal):acc(acc),bal(bal),last_upd(d){}
  void set_bal(int x){bal=x;}
  float get_bal(){return bal;}
  int get_acc(){return acc;}
  void show_balance(){cout<<acc<<": "<<last_upd<<"\t"<<"Rupees "<<bal<<endl;}
};

class transaction{
  int acc;
  float aot;
  type t;
  string dot;
  public:
  transaction(int acc,const string& d,float a,type t):acc(acc),dot(d),aot(a),t(t){}
  string get_dot(){return dot;}
  void deposit(balance* b){b->set_bal(aot);}
  void withdraw(balance *b){if(b->get_bal()>=aot)b->set_bal((b->get_bal()-aot));else{cout<<"Insufficient balance"<<endl;t=I;}}
  void show_transaction(){cout<<acc<<": "<<dot<<"\tRupees "<<aot<<"\t"<<t<<endl;}
};

class account{
  vector<transaction> t;
  balance *b;
  static int acc;
  public:
  account(const string& d,int bal=0){b = new balance(acc,d,bal);acc++;}
  void transact(int type,float amt,const string& d){
     transaction t1(b->get_acc(),d,amt,static_cast<enum type>(type));
     if(type==W){
       t1.withdraw(b);
     }else{
       t1.deposit(b);
     }
     t.push_back(t1);
  }

  void find_transactions(const string& d){
     b->show_balance();
     int c = 0;
     for(auto itr = t.begin();itr!=t.end();++itr)
        if(itr->get_dot()==d){
          itr->show_transaction();
          c++;
        }
     if(c>0)
        cout<<c<<" transaction(s) was/were made on "<<d<<endl;
     else
        cout<<"No such transaction"<<endl;
  }
  void list_transactions(){
     b->show_balance();
     for(auto itr = t.begin();itr!=t.end();++itr)
          itr->show_transaction();
  }
};

int account::acc = 1000;

int main()
{
 account a("22/10/23");
 a.transact(W,10000,"23/10/23");
 //a.transact(D,10000,"23/10/23");
 a.transact(W,9000,"24/10/23");
 a.find_transactions("24/10/23");
 a.list_transactions();
 return 0;
}

