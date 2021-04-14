/*Design the class(es) for the following. Each account has account number and balance amount. A list of account is to be maintained where one can add and find account, display information of all accounts. While adding, account number must be unique. Withdraw object has account number (must exist) and amount (will not exceed balance amount of corresponding account). Withdraw object will update the balance of corresponding account in the list. Implement your design. Use friend function wherever required and again, modify your implementation to avoid friend function.*/

#include <iostream>
#include <vector>
using namespace std;
const int accounts = 100;

class account{
  static int ids;
  float balance;
  int id;
  public:
  static vector<account*> accs;
  account(float balance = 0):balance(balance){id=ids;accs.push_back(this);ids++;}
  friend ostream& operator<<(ostream& o,const account* x);
  static void show_all_accounts(){
     cout<<"A "<<"B"<<endl;
     for(int i=0;i<accs.size();i++){
        cout<<accs[i]<<endl;
     }
  }
  int get_acc_num(){return id;}
  int get_bal(){return balance;}
  void set_bal(int x){balance = x;}
  static void find_account(int id){
      for(int i=0;i<accs.size();i++)
         if(accs[i]->id==id){
            cout<<"A "<<"B"<<endl;
            cout<<accs[i]<<endl;
            return;
         }
      
      cout<<"Account not found"<<endl;
  }
};

int account::ids = 1;
vector<account*> account::accs;
ostream& operator<<(ostream& o,const account* x){
   cout<<x->id<<" "<<x->balance;return o;
}

class Withdraw{
  int amount;
  int acc;
  public:
  void withdraw(int acc,int amt){
     for(int i=0;i<account::accs.size();i++)
        if(account::accs[i]->get_acc_num() == acc){
          if(amt<=account::accs[i]->get_bal())
            account::accs[i]->set_bal((account::accs[i]->get_bal()-amt));
          else
            cout<<"Insufficient balance"<<endl;
          return;
        };

    cout<<"No such account"<<endl;
  }
};

int main()
{
 account x;
 Withdraw w;
 w.withdraw(x.get_acc_num(),100);
 x.set_bal(1000);
 w.withdraw(x.get_acc_num(),100);
 account y;
 account::find_account(2);
 account::show_all_accounts();
 return 0;
}

