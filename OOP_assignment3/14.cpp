/*Design the class(es) for the following scenario:
• An item list contains item code, name, rate, and quantity for several
items.
• Whenever a new item is added in the list uniqueness of item code is to be
checked.
• Time to time rate of the items may change.
• Whenever an item is issued or received existence of the item is checked
and quantity is updated.
• In case of issue, availability of quantity is also to be checked.
• User may also like to know price/quantity available for an item.*/

#include <iostream>
#include <vector>
using namespace std;

struct item{
  int code;
  string name;
  float rate;
  int qty;
};
ostream& operator<<(ostream& o,const item& i){
  o<<i.code<<" "<<i.name<<" "<<i.rate<<" "<<i.qty;
  return o;
}

class item_list{
  public:
  vector<item> vi;
  void add_to_vi(const item& i){vi.push_back(i);}
  void print_list(){
   for(auto itr = vi.begin();itr!=vi.end();++itr)
      cout<<*itr<<endl;
  }
  item* find_item(int c){
    for(auto itr = vi.begin(); itr!=vi.end();++itr)
       if(itr->code==c)
         return &(*itr);
    return nullptr;
  }
};

class User{
  item_list il; 
  public:
  void add_item(int c,const string& n,float r,int q){
     int in = c;
     item *x = il.find_item(c);
     while(x!=nullptr && x->name!=n){//code is already present with a product of a different name.
       cout<<"Item already present: "<<*x<<endl<<"Enter a valid code(Press -1 to cancel this product): ";
       cin>>in;
       x = il.find_item(in);
     }
     if(in==-1)//cancel this product
       return;
     
     if(x!=nullptr && x->name==n)//over write the previous product of same name and code.
        il.vi.erase(il.vi.begin()+(x-&(il.vi[0])));

     item i = {in,n,r,q};
     il.add_to_vi(i);
  }
  void add_item(item& i){
     add_item(i.code,i.name,i.rate,i.qty);
  }

  void change_rate(int code,float rate){
     item* x = il.find_item(code);
    if(x)
     x->rate = rate;
  }  

  item* check_availability(int code){
    item* x;
    if((x=il.find_item(code))){
      cout<<*x<<endl;
      return x;
    }else{
      cout<<"No such item in inventory"<<endl;
      return nullptr;
    }
  }

  void issue_item(int code,int num){
     item* x = check_availability(code);
     if(x!=nullptr && x->qty>=num){
       x->qty-=num;
     }
  }
  
  void print_list(){il.print_list();}
};

int main()
{
 User user;
 item i = {1001,"kola",22.50,10};
 user.add_item(i);
 user.issue_item(1001,3);
 user.change_rate(1001,24);
 user.check_availability(1001);
 item b = {1001,"kola",28.50,12};
 user.add_item(b);
 user.issue_item(1002,10);
 user.issue_item(1001,1);
 user.add_item(1001,"ola",23,20);
 user.print_list();
 return 0;
}

