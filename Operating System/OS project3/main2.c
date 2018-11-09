#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

#define MODE S_IRWXU | S_IXGRP | S_IROTH | S_IXOTH 

char buf[60000000];
void my_test(int count,int num);
int main()
{
	int status;
	for(int i=1;i<24;i++){
		int pid=fork();
		if(pid==0){
			int _pid=getpid();
			my_test(i,_pid);
		}
		else {
			while(waitpid(-1,&status,0)!=-1){}
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
	//handle=open("/usr/myfile/dummy.txt",O_RDONLY,MODE);
	if(handle ==-1) {
		printf("ErrorOpeningFile\n");
		exit(1);
	}
	srand(time(NULL));

	gettimeofday(&start,NULL);
	/*
	for(int i=0;i<12;i++){
		if(getpid()==num) pid=fork();	
		else break;	
	}
	lseek(handle,offset,SEEK_SET);
	for (int j=0;j<100000;j++){
		//offset=rand()%1024;
		//lseek(handle,offset,SEEK_SET);
		int bytes=read(handle,buf,size);
		//if(bytes==-1) printf("read error\n");																								)
	}
	*/
	for(int i=0;i<20;i++){
		int pid=fork();
		if(pid==0){
			//offset=rand()%2048;
			//lseek(handle,offset,SEEK_SET);
			handle=open("/usr/dummy.txt",O_RDONLY,MODE);
			for(int j=0;j<100000;j++){
				int bytes=read(handle,buf,size);
				if(bytes==-1){
					printf("read error!\n");
					lseek(handle,0,SEEK_SET);
					j--;
				}
				
			}
			close(handle);
			exit(0);
		}
	}
	for(int i=0;i<12;i++){
		waitpid(-1,&status,0);
	}
	//if(getpid()!=num) exit(0);
	//else while(waitpid(-1,&status,0)!=-1){}
	gettimeofday(&end,NULL);
	diff=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
	long long unsigned res=100000*size*12/diff;
	double result=res*1000000/1024/1024;
	printf("%d %lu %lf\n",size,diff,result);
	
	close(handle);
	exit(0);

}