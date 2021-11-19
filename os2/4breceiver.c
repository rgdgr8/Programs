#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 100

// structure for message
struct mesg_buffer {
	long mesg_type;
	char mesg_text[MAX*10];
} message;

int main()
{
	key_t key;
	int msgid;

	// ftok to generate unique key
	key = ftok("/tmp", 65);

	msgid = msgget(key, 0666 | IPC_CREAT);
	
	do{
		//receive msg from Receiver
		 msgrcv(msgid, &message, sizeof(message), 1, 0);
		 if(strlen(message.mesg_text)==2 && message.mesg_text[0]=='x')
			 break;
		 printf("Received from Caller: %s",message.mesg_text);
		
		 message.mesg_type = 1;
		 printf("Press enter to send: ");
		 fgets(message.mesg_text,MAX,stdin);

		 // msgsnd to send message(including '\n')
		 msgsnd(msgid, &message, sizeof(message), 0);
		 if(strlen(message.mesg_text)==2 && message.mesg_text[0]=='x'){
			 sleep(2);
			 msgctl(msgid, IPC_RMID, NULL);
			 break;
		 }
		 // display the sent message
		 printf("Sent to Caller: %s\n", message.mesg_text);

		 sleep(2);
	 }while(1);

	return 0;
}
