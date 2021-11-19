#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <queue>
#include "consts.h"
#define MIN(a, b) ((a) < (b)) ? (a) : (b)
using namespace std;

int ptime = 0;

typedef struct job{
	int id;
	int prior;
	int arr;
	int currarrt;
	int bursts[BURSTS];
	int bsize;
	int curi;

	int endt;
	int cput;
	int iot;
}job;
job terminated[JOBS];
int termcount = 0;

void fcfs();
void priority();
void rr();

template<class T>
void printq(priority_queue<job,vector<job>,T> q){
	while(!q.empty()){
		job i = q.top();q.pop();
		printf("id=%d,prior=%d,arrt=%d,endt=%d,cput=%d,iot=%d\n",i.id,i.prior,i.arr,i.endt,i.cput,i.iot); 
	}
}

template<class T>
void readfile(priority_queue<job,vector<job>,T>& q){
	FILE* file = fopen("jobs","r");

	for(int i=0;i<JOBS;i++){
		job j;
		
		fscanf(file,"%d %d %d",&(j.id),&(j.prior),&(j.arr));
		j.currarrt = j.arr;

		int burst = 0;
		j.bsize = 0;
		j.curi = 0;
		j.cput = 0;
		j.iot = 0;
		while(1){
			fscanf(file,"%d",&burst);
			if(burst==-1)
				break;

			j.bursts[j.bsize++] = burst;
			if(j.bsize%2!=0)
				j.cput += burst;
			else
				j.iot += burst;
		}
		q.push(j);
	}

	fclose(file);
	//exit(0);
}

int main(){
	int opt;
	printf("1.FCFS\n2.PRIORITY\n3.RR\n");
	scanf("%d",&opt);

	switch(opt){
		case 1: fcfs();break;
		case 2: priority();break;
		case 3: rr();
	}

	double wt = 0;
	for(int i=0;i<termcount;i++){
		int w = terminated[i].endt - (terminated[i].cput + terminated[i].iot);
		wt += w;
		printf("id=%d,arrt=%d,endt=%d,cput=%d,iot=%d,turnaround=%d,waiting=%d\n",terminated[i].id,terminated[i].arr,terminated[i].endt,terminated[i].cput,terminated[i].iot,(terminated[i].endt-terminated[i].arr),w); 
	}
	printf("Average waiting time for these %d processes is: %lf\n",JOBS,(wt/JOBS));

	return 0;
}

class fcfs_comp{
	public:
	bool operator()(const job& a,const job& b){
		return a.currarrt>b.currarrt;
	}
};

void fcfs(){
	priority_queue<job,vector<job>,fcfs_comp> readyq;
	readfile(readyq);

	while(!readyq.empty()){
		job j = readyq.top();
		readyq.pop();

		if(ptime>=j.currarrt){
			ptime += j.bursts[j.curi++];//add burst duration to current time
		}else{//if io hasn't ended yet
			ptime += (j.currarrt-ptime);//add remaining io duration to current time
			ptime += j.bursts[j.curi++];
		}
		if(j.curi>=j.bsize){//if this was the last burst
			j.endt = ptime;
			terminated[termcount++] = j;
			continue;
		}

		j.currarrt = ptime+j.bursts[j.curi++];//set next q arrival time for this job to current_time+next_io_burst_duration
		readyq.push(j);
	}
}

class priority_comp{
	public:
	bool operator()(const job& a,const job& b){
		if(a.prior==b.prior)//if priority is same, select by fcfs
			return a.currarrt>b.currarrt;
		return a.prior>b.prior;
	}
};

void priority(){
	priority_queue<job,vector<job>,priority_comp> readyq;
	readfile(readyq);

	while(!readyq.empty()){
		job j = readyq.top();
		readyq.pop();

		if(ptime>=j.currarrt){
			ptime += j.bursts[j.curi++];
		}else{//if the next highest priority job's arrival time hasn't come yet or its io isn't complete yet
			//printf("Rejecting id=%d,prior=%d,arrt=%d,endt=%d,cput=%d,iot=%d\n",j.id,j.prior,j.currarrt,j.endt,j.cput,j.iot); 
			job jobs[JOBS];
			int i = 0;
			jobs[i++] = j;
			while(!readyq.empty()){//extract all the jobs
				j = readyq.top();
				readyq.pop();
				jobs[i++] = j;
			}

			priority_queue<job,vector<job>,fcfs_comp> tempq;
			for(int k=0;k<i;k++){//put back all the extracted jobs into an fcfs queue
				tempq.push(jobs[k]);
			}

			j = tempq.top();//get the job with the next smallest currarrt
			for(int k=0;k<i;k++){//put back all the extracted jobs (except for the fcfs top) into the ready queue
				if(jobs[k].id!=j.id)
					readyq.push(jobs[k]);
			}
			//printf("Accepting id=%d,prior=%d,arrt=%d,endt=%d,cput=%d,iot=%d\n",j.id,j.prior,j.currarrt,j.endt,j.cput,j.iot); 
			if(ptime<j.currarrt)//if still the current time hasn't reached the currarrt
				ptime += (j.currarrt-ptime);//add remaining time till arrival or remaining io duration to current time
			ptime += j.bursts[j.curi++];
		}
		if(j.curi>=j.bsize){
			j.endt = ptime;
			terminated[termcount++] = j;
			continue;
		}

		j.currarrt = ptime+j.bursts[j.curi++];
		readyq.push(j);
	}
}

void rr(){
	priority_queue<job,vector<job>,fcfs_comp> readyq;
	readfile(readyq);

	while(!readyq.empty()){
		job j = readyq.top();
		readyq.pop();

		if(ptime<j.currarrt){//if io incomplete or unarrived
			ptime += (j.currarrt-ptime);//add remaining io duration to current time
		}
		if(j.bursts[j.curi]>slice){//if cpu duration left 
			ptime += slice;
			j.bursts[j.curi] -= slice;
			j.currarrt = ptime;
		}else{
			ptime += j.bursts[j.curi++];
			if(j.curi>=j.bsize){//if this was the last burst
				j.endt = ptime;
				terminated[termcount++] = j;
				continue;
			}
			j.currarrt = ptime+j.bursts[j.curi++];
		}

		readyq.push(j);
	}
}
