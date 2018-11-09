#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

#define MAX_SIZE 102400000
#define MODE S_IRWXU | S_IXGRP | S_IROTH | S_IXOTH 

char string[MAX_SIZE];

void my_test(int count,int num);
int main()
{
	
	
	for(int i=1;i<15;i++){
		int pid=fork();
		if(pid==0){
			int _pid=getpid();
			my_test(i,_pid);
		}
		else {
			while(wait(NULL)!=-1){}
		}
	}
}


void my_test(int count,int num)
{
	int handle,status;	
	struct timeval start,end;
	long unsigned diff;
	int size=2<<count;//bytes
	int pid;
	int offset=0;
	for(int i=0;i<MAX_SIZE;i++){
		string[i]='a';
	}
	handle=open("/usr/myfile/write_test.txt",O_WRONLY|O_APPEND);
	if(handle ==-1) {
		printf("ErrorOpeningFile\n");
		exit(1);
	}
	srand(time(NULL));

	gettimeofday(&start,NULL);

	for(int i=0;i<20;i++){
		int pid=fork();
		if(pid==0){
			//offset=rand()%2048;
			lseek(handle,offset,SEEK_SET);
			for(int j=0;j<1000;j++){
				int bytes=write(handle,string,size);
				if(bytes==-1){
					//printf("write error!\n");
					lseek(handle,0,SEEK_SET);
					j--;
				}
				
			}
			exit(0);
		}
	}
	for(int i=0;i<20;i++){
		waitpid(-1,&status,0);
	}
	//if(getpid()!=num) exit(0);
	//else while(waitpid(-1,&status,0)!=-1){}
	gettimeofday(&end,NULL);
	diff=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
	long long unsigned res=1000*size*20/diff;
	double result=res*1000000/1024/1024;
	
	printf("%d %lu %lf\n",size,diff,result);
	
	close(handle);
	exit(0);

}


