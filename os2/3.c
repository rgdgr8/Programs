#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>

sem_t *mutex;
sem_t *wrt;
int *readcount;
int *shared;

void reader(int);
void writer(int);
int p,c;

int main(){
	shared = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	readcount = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*shared = 0;
	*readcount = 0;

	//sem_init(&mutex,1,1);
	//sem_init(&wrt,1,1);
	mutex = sem_open("mutex",O_CREAT,0666,1);
	wrt = sem_open("wrt",O_CREAT,0666,1);

	printf("Enter writer count: ");
	scanf("%d",&p);	
	printf("Enter reader count: ");
	scanf("%d",&c);

	int pids[p+c];
	int ids = 0;

	for(int i=1;i<=p;i++){
			if((pids[ids++]=fork())==0){//writer
				printf("writer %d initialised\n",i);
				writer(i);
				return 0;
			}
	}
	for(int i=1;i<=c;i++){
			if((pids[ids++]=fork())==0){//reader
				printf("Reader %d initialised\n",i);
				reader(i);
				return 0;
			}
	}
	
	int killed;	
	if((killed=wait(NULL))>0){//kill all processes when one is killed
		for(int i=0;i<ids;i++){
			if(pids[i]!=killed)
				kill(pids[i],SIGTERM);
		}	
	}

	printf("mutex unlinked = %d\n",!sem_unlink("mutex"));
	printf("wrt unlinked = %d\n",!sem_unlink("wrt"));
}

void writer(int v){
	do{
		int x = 0;
		while(x!=v){
			scanf("%d",&x);
			if(x==0)
				return;
		}

		printf("***************Writer%d will write****************\n",v);
		
		sem_wait(wrt);

		*shared = v;

		sem_post(wrt);
	}while(1);
}

void reader(int v){
	do{
		sem_wait(mutex); 
		(*readcount)++;
		if(*readcount==1)
			sem_wait(wrt); 
		sem_post(mutex);

		printf("Reader%d read v=%d\n",v,*shared);

		sem_wait(mutex); 
		(*readcount)--;
		if (*readcount==0)
			sem_post(wrt); 
		sem_post(mutex);

		sleep(3);//wait time for user to input a writer id
	}while(1);
}
