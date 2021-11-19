#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <string.h> 
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/semaphore.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUFFER_SIZE 50 

void append(char*,int);
void listener(int, char*);
sem_t *mutex;

int main(void)
{
	int list;
	printf("Enter number of listeners: ");
	scanf("%d",&list);
	fflush(stdin);

	char* paths[list];
	int pids[list];
	//sem_init(&mutex,1,1);
	mutex = sem_open("mutex",O_CREAT,0666,1);	

	for(int i=1;i<=list;i++){
		char pathname[50];
		sprintf(pathname,"/tmp/myfifo%d",i);
		paths[i-1] = malloc(50);
		strcpy(paths[i-1],pathname);

		//create the pipe
		if(mkfifo(pathname,0666) == -1) {
			printf("Pipe creation failed for child%d\n",i);
			return 1; 
		}

		if((pids[i-1]=fork())==0) { // child process
			//printf("child%d forked",i);
			listener(i,pathname);
			return 0;
		}
	}

	char* queries[list];
	int qsize = 0;
	do{
		for(int i=0;i<list;i++){
			char msg[BUFFER_SIZE];
			int fd = open(paths[i],O_RDONLY);
			queries[i] = malloc(BUFFER_SIZE);
			if(read(fd,msg,BUFFER_SIZE)>0){
				printf("Request from listener%d: %s",i+1,msg);
				strcpy(queries[qsize],msg);
				(qsize)++;
			}
			close(fd);
		}

		if(qsize<1){
			char msg [BUFFER_SIZE];
			printf("Broadcast: ");	
			//scanf("%s",write_msg);
			fgets(msg, BUFFER_SIZE, stdin);
			if(strlen(msg)==2 && msg[0]=='x'){
				for(int i=0;i<list;i++){
					kill(pids[i],SIGTERM);
					unlink(paths[i]);
				}
				break;
			}
			
			for(int i=0;i<list;i++){
				int fd = open(paths[i],O_WRONLY);
				write(fd, msg, BUFFER_SIZE);
				close(fd);
			}
		}else{
			for(int i=0;i<list;i++){
				int fd = open(paths[i],O_WRONLY);
				for(int j=0;j<qsize;j++){
					char query[BUFFER_SIZE];
					sprintf(query,"Response to %s",queries[j]);
					write(fd, query, BUFFER_SIZE);
				}
				close(fd);
			}
			qsize = 0;
		}
	}while(1);

	while(wait(NULL)>0);
	sem_unlink("mutex");
	printf("Done\n");

	return 0;
}

void listener(int id, char* path){
	char msg[BUFFER_SIZE]; 
	do{

		int fd = open(path,O_WRONLY);
/*mutually exclusive for listeners, since the prompt needs to displayed for one listener at a time*/
		sem_wait(mutex);

		printf("listener%d Query: ",id);
		fgets(msg,BUFFER_SIZE,stdin);

		sem_post(mutex);	

		if(strlen(msg)>2 || msg[0]!='x')
			write(fd,msg,BUFFER_SIZE);//send excluding the newline char
		close(fd);
		
		fd = open(path,O_RDONLY);
		while(read(fd, msg, BUFFER_SIZE)>0)
			printf ("child%d read %s", id, msg);
		close(fd);
	}while(1);
}
