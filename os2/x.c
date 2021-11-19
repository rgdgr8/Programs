#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include "cqueue.c"

int *mutex;
int *total;
int *filled;
int *empty;
char pro[10] = "Producer";
char con[10] = "Consumer";

void swait(char* s, int id, int* syn){//function needs to be atomic
	while(*syn<=0);
	(*syn)--;
	//printf("Waited by %s%d, syn=%d\n",s,id,*syn);
}

void ssignal(char* s,int id, int* syn){
	(*syn)++;
	//printf("Signaled by %s%d, syn=%d\n",s,id,*syn);
}

void producer(int);
void consumer(int);
int p,c;

int main(){
	mutex = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	total = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	rear = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	front = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	items = mmap(NULL,SIZE*sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	filled = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	empty = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	*mutex = 1;
	*total = 0;
	*rear = -1;
	*front = -1;
	*filled = 0;
	*empty = SIZE;

	printf("Enter p: ");
	scanf("%d",&p);	
	printf("Enter c: ");
	scanf("%d",&c);

	for(int i=1;i<=p;i++){
			if(fork()==0){//producer
				//printf("producer %d\n",i);
				producer(i);
				return 0;
			}
	}
	for(int i=1;i<=c;i++){
			if(fork()==0){//consumer
				//printf("consumer %d\n",i);
				consumer(i);
				return 0;
			}
	}

	int t = 0;
	while(wait(NULL)>0){
		t++;
		if(t>=c){
			printf("Total=%d\n",*total);
			exit(0);
		}
		//printf("Waiting for children to terminate\n");
	}

}

void producer(int v){
	while(1){
		swait("Producer 'empty'",v,empty);
		swait(pro,v,mutex);

		if(enQueue(v)==0)
			; //printf("Enqueue failed for Production of %d\n",v);
		printf("Produced %d:\n",v);
		//display();

		ssignal(pro,v,mutex);
		ssignal("Producer 'filled'",v,filled);
	
		v += p;
	}
}
void consumer(int id){
	swait("Consumer 'empty'", id, filled);
	swait(con, id, mutex);

	int v = deQueue();
	if(v>0){
		*total = *total + v;
		//printf("cur_total=%d,dequed(v)=%d after %s%d\n",*total,v,con,id);
	}//else printf("Dequeue failed for %s%d\n",con,id);

	ssignal(con, id, mutex);
	ssignal("Consumer 'filled'", id, empty);
}
