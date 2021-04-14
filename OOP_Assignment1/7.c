#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int nodes = 0;//number of nodes
int n;//number of subjects

typedef struct student{
 int roll;
 int* scores;
 char name[100];
}student;

typedef struct node{
 student s;
 struct node *next;
}node;

void create(node **h,node **t,student x);
void insert(node **h,node **t,student x,int pos);
void delete(node **h,node **t,int pos);

void print_list(node *h){
 int k = 1;
 for(;h!=NULL;h=h->next){
     printf("%d)\nRoll: %d  Name: %s\nScores: ",k,h->s.roll,h->s.name);
     k++;
     for(int i=0;i<n;i++)
        printf("%d ",h->s.scores[i]);
     printf("\n");
 }
}

void input(student *s){
 printf("Enter a Roll Number and a Name: ");
 scanf("%d %s",&(s->roll),s->name);
 s->scores = malloc(n*sizeof(int));
 for(int i=1;i<=n;i++){
    printf("Enter a score for Subject #%d: ",i);
    scanf("%d",&(s->scores[i-1]));
 }
}

int main()
{
 node *head,*tail;
 student s;
 printf("Enter the number of subject: ");
 scanf("%d",&n);
 input(&s);
 create(&head,&tail,s);//list created and first node added.
 char c;
do{
 printf("Type d/D to delete an element, i/I to insert an element, p/P for printing the list: ");
// c = getchar();
 scanf(" %c",&c);
 int p;
 if(c=='d' || c=='D'){
   do{
    printf("Enter a position to delete: ");
    scanf("%d",&p);
   }while(p<=0 && p>nodes);
   delete(&head,&tail,p);
 }else if(c=='i' || c=='I'){
   do{
    printf("Enter a position to insert in: ");
    scanf("%d",&p);
   }while(p<=0);
   input(&s);
   if(nodes>0)
     insert(&head,&tail,s,p);
   else
     create(&head,&tail,s);
 }else {
  print_list(head);
 }
}while(c=='i' || c=='I' || c=='p' || c=='P' || c=='d' || c=='D');
 return 0;
}

void create(node **h,node **t,student x){
 node *newNode = malloc(sizeof(node));
 newNode->s = x;
 newNode->next = NULL;
 *h = newNode;
 *t = *h;
 nodes++;
}
void insert(node **h,node **t,student x,int pos){
 if(pos<1){//illegal position
   printf("No such Position!\n");
   return;
 }

 if(pos>=(nodes+1)){//append to the end of the list
   node *newNode = malloc(sizeof(node));
   newNode->s = x;
   newNode->next = NULL;
   (*t)->next = newNode;
   *t = newNode;
   nodes++;
   return;
 }

 /*------Insert in middle or front------*/
 node *temp = *h;
 int traversed = 1;
 while(traversed<(pos-1)){
      temp = temp->next;
      traversed++;
 }
 node *newNode = malloc(sizeof(node));
 newNode->s = x;
 if(pos>1){
   newNode->next = temp->next;
   temp->next = newNode;
 } 
 else{
   newNode->next = *h;
   *h = newNode;
   if(nodes<1)
     *t = *h;
 }
 nodes++;
}

void delete(node **h,node **t,int pos){
 if(pos>nodes || pos<1){//illegal position
   printf("No such data!\n");
   return;
 }
 node *temp = *h;
 if(pos==1){//deleting first node
   *h = (*h)->next;
   free(temp);
   nodes--;
   return;
 }
 
/*-----deleting any other node than first node-----*/
 int traversed = 1;
 while(traversed<(pos-1)){
      temp = temp->next;
      traversed++;
 }
 if(temp->next->next==NULL)
    *t = temp;
 node *del = temp->next;
 temp->next = temp->next->next;
 free(del);
 nodes--;
}
