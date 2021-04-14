/*Create a class for linked list. Consider a separate class NODE for basic node activities and use it in class for linked list.*/

#include<iostream>
using namespace std;

class node{
 int s;
 node *next;
 node *head;
 node *tail;
 public:
 static int nodes;
 void create(int x);
 void insert(int x,int pos);
 void remove(int pos);
 void print_list(){
  node *h = head;
  for(;h!=NULL;h=h->next){
      cout<<h->s<<"->";
  }
  cout<<"NULL"<<endl;
 }
};

class List{
 node n;
 public:
 List(int v){n.create(v);}
 void push_back(int v){n.insert(v,(node::nodes)+1);}
 void push_front(int v){n.insert(v,1);}
 void insert(int v,int pos){n.insert(v,pos);}
 void pop_back(){n.remove(node::nodes);}
 void pop_front(){n.remove(1);}
 void remove(int pos){n.remove(pos);}
 void display(){n.print_list();}
 int count(){return node::nodes;}
};

int node::nodes = 0;

int main()
{
 List l(11);
 for(int i=0;i<5;i++)
    l.push_back(i+20);
 l.display();cout<<l.count()<<endl;
 for(int i=0;i<5;i++)
    l.push_front(i+200);
 l.display();cout<<l.count()<<endl;
 for(int i=0;i<5;i++)
    l.pop_front();
 l.display();cout<<l.count()<<endl;
 for(int i=0;i<5;i++)
    l.pop_back();
 l.display();cout<<l.count()<<endl;
 
 for(int i=0;i<5;i++)
    l.insert(i*2,i+2);
 l.display();cout<<l.count()<<endl;
 for(int i=0;i<5;i++)
    l.insert(i*10,i+4);
 l.display();cout<<l.count()<<endl;
 for(int i=0;i<5;i++)
    l.remove(i);
 l.display();cout<<l.count()<<endl;
 return 0;
}

void node::create(int x){
 node *newNode = new node;
 newNode->s = x;
 newNode->next = NULL;
 head = newNode;
 tail = head;
 node::nodes++;
}
void node::insert(int x,int pos){
 if(pos<1){//illegal position
   printf("No such Position!\n");
   return;
 }
  
 if(pos>(nodes+1)){
   cout<<"Total number of nodes present is "<<nodes<<" so appending nodes to the current list at "<<(nodes+1)<<" position"<<endl;
 }

 if(nodes==0){
    node::create(x);
    return;
 }

 if(pos>=(nodes+1)){//append to the end of the list
   node *newNode = new node;
   newNode->s = x;
   newNode->next = NULL;
   tail->next = newNode;
   tail = newNode;
   node::nodes++;
   return;
 }

 /*------Insert in middle or front------*/
 node *temp = head;
 int traversed = 1;
 while(traversed<(pos-1)){
      temp = temp->next;
      traversed++;
 }
 node *newNode = new node;
 newNode->s = x;
 if(pos>1){
   newNode->next = temp->next;
   temp->next = newNode;
 } 
 else{
   newNode->next = head;
   head = newNode;
   if(nodes<1)
     tail = head;
 }
 node::nodes++;
}

void node::remove(int pos){
 if(pos>nodes || pos<1){//illegal position
   printf("No such data!\n");
   return;
 }
 node *temp = head;
 if(pos==1){//deleting first node
   head = head->next;
   delete temp;
   node::nodes--;
   return;
 }
 
/*-----deleting any other node than first node-----*/
 int traversed = 1;
 while(traversed<(pos-1)){
      temp = temp->next;
      traversed++;
 }
 if(temp->next->next==NULL)
    tail = temp;
 node *del = temp->next;
 temp->next = temp->next->next;
 delete del;
 node::nodes--;
}
