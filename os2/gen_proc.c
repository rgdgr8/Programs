#include <stdio.h>
#include <stdlib.h>
#include "consts.h"

int main(){
	FILE* f = fopen("jobs","w");
	
	for(int i=1;i<=JOBS;i++){
			fprintf(f,"%d ",i);
			int prior = rand()%JOBS + 1;
			fprintf(f,"%d ",prior);
			fprintf(f,"%d ",(i*2));
			int bursts = rand()%BURSTS+1;
			if(bursts%2==0)//so that the process does not end with io burst
				bursts--;
			for(int j=0;j<bursts;j++){
				if(j%2==0)
					fprintf(f,"%d ",(rand()%BURST_TIME+1));
				else
					fprintf(f,"%d ",(rand()%BURST_TIME+1));
			}
			fprintf(f,"-1\n");
	}

	fclose(f);
}
