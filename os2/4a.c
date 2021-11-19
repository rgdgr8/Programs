#include <sys/types.h> 
#include <stdio.h> 
#include <signal.h> 
#include <string.h> 
#include <sys/wait.h>
#include <unistd.h>
#define BUFFER_SIZE 25 
#define READ_END 0 
#define WRITE_END 1

void listener(int, int*);
char read_msg[BUFFER_SIZE]; 

int main(void)
{
	int list;
	printf("Enter number of listeners: ");
	scanf("%d",&list);

	int write_fds[list];
	int pids[list];

	for(int i=1;i<=list;i++){
		int fd[2];
		//create the pipe
		if(pipe(fd) == -1) {
			printf("Pipe creation failed for child%d\n",i);
			return 1; 
		}

		if((pids[i-1]=fork())==0) { // child process
			//printf("child%d forked",i);
			listener(i,fd);
			return 0;
		}

		close(fd[READ_END]);//close the unused read ends for parent process
		write_fds[i-1] = fd[WRITE_END];//store the end for each fork for closing later
	}


	fflush(stdin);
	char write_msg[BUFFER_SIZE];
	do{
		printf("Broadcast: ");	
		//scanf("%s",write_msg);
		fgets(write_msg, BUFFER_SIZE, stdin);
		if(strlen(write_msg)==2 && write_msg[0]=='x'){
			for(int i=0;i<list;i++)
				kill(pids[i],SIGTERM);
			break;
		}

		for(int i=0;i<list;i++){
			write(write_fds[i], write_msg, BUFFER_SIZE);
		}
		sleep(1);//so that listeners get time to print
	}while(1);

	for(int i=0;i<list;i++)
		close(write_fds[i]);//close write ends for parent

	while(wait(NULL)>0);
	printf("Done\n");

	return 0;
}

void listener(int id, int* fd){
	close(fd[WRITE_END]);//close unused end for child process
	do{
		read(fd[READ_END], read_msg, BUFFER_SIZE);
		printf ("child%d read %s", id, read_msg);
	}while(1);
}
