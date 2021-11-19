#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "cqueue.c"

sem_t *mutex;
sem_t *filled;
sem_t *empty;
int *total;

void producer(int);
void consumer(int);
int p,c;

int main(){
	total = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	rear = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	front = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	items = mmap(NULL,SIZE*sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	*total = 0;
	*rear = -1;
	*front = -1;

	mutex = sem_open("mutex",O_CREAT,0666,1);
	empty = sem_open("empty",O_CREAT,0666,SIZE);
	filled = sem_open("filled",O_CREAT,0666,0);

	printf("Enter p: ");
	scanf("%d",&p);	
	printf("Enter c: ");
	scanf("%d",&c);

	int pids[p];

	for(int i=1;i<=p;i++){
			if((pids[i-1]=fork())==0){//producer
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

	int killedconsumers = 0;
	while(wait(NULL)>0){
		killedconsumers++;
		if(killedconsumers==c){//if all consumers are dead, kill the producers
			for(int i=0;i<p;i++)
				kill(pids[i],SIGTERM);

			printf("\nTotal=%d\n",*total);
		}
	}
	
	printf("mutex unlinked = %d\n",!sem_unlink("mutex"));
	printf("empty unlinked = %d\n",!sem_unlink("empty"));
	printf("filled unlinked = %d\n",!sem_unlink("filled"));
}

void producer(int v){
	do{
		sem_wait(empty);
		sem_wait(mutex);
	
		if(enQueue(v)==0) {
			v -= p; 
			printf("Enqueue failed for Production of %d at rear=%d,front=%d\n",v,*rear,*front);
		}
		else printf("Produced %d at rear=%d,front=%d\n",v,(*rear),(*front));
		//display();

		sem_post(mutex);
		sem_post(filled);

		v += p;
	}while(1);
}
void consumer(int id){
	sem_wait(filled);
	sem_wait(mutex);

	int v = deQueue();
	if(v>0){
		*total = *total + v;
		printf("**********consumed %d from rear=%d,front=%d***************\n",v,(*rear),(*front)-1);
	}else printf("Dequeue failed for consumer%d from rear=%d,front=%d\n",id,*rear,*front);

	sem_post(mutex);
	sem_post(empty);
}
