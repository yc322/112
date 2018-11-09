#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#define STD_INPUT 0
#define STD_OUTPUT 1
#define NUM 1024

enum specify{NORMAL,OUT_REDIRECT,IN_REDIRECT,APPEND};
char command[100][30];
int list_num;
char args[NUM][NUM];


int mystrtok2(char *argv[],char *string)
{
    int i=0,j=0,state=0;
    strcat(string," ");
    while(*string){
        switch(state)
        {
        case 0:
            if(!isspace(*string)) state=1;
            else string++;
            break;
        case 1:
            if(isspace(*string)){
                args[i][j]='\0';
                argv[i]=args[i];
                i++;
                j=0;
                state=0;
            }
            else{
                args[i][j]=*string;
                j++;
            }
            string++;
            break;
        }
    }
    return i;
}

int Accomp(char *argv[],int count)
{
    char *arg[50],*arg1[20],*arg2[20];
    int i,j;
    int fd,fd1;
    char *filename,*path;
    enum specify type=NORMAL;
    for (i=0;i<count;i++){
        arg[i]=argv[i];
    }
    arg[i]=NULL;
    if(strcmp(arg[count-1],"<")==0 || strcmp(arg[count-1],">")==0 || strcmp(arg[count-1],"|")==0){
       printf("error:command error!\n");
       return 0;
    }
    for (i=0;i<count;i++){
        if(strcmp(arg[i],"<")==0){
            filename=arg[i+1];
            arg[i]=NULL;
            type=IN_REDIRECT;
        }
        else if(strcmp(arg[i],">")==0){
            filename=arg[i+1];
            arg[i]=NULL;
            type=OUT_REDIRECT;
        }
        else if(strcmp(arg[i],">>")==0){
            filename=arg[i+1];
            type=APPEND;
            arg[i]=NULL;
        }
    }
    switch(type)
    {
    case NORMAL:
        execvp(arg[0],arg);
        break;
    case IN_REDIRECT:
        fd=open(filename,O_RDONLY);
        dup2(0,fd1);//save std output
        dup2(fd,0);
        close(fd);
        execvp(arg[0],arg);
        dup2(fd1,0);
        break;
    case OUT_REDIRECT:
        fd=open(filename,O_WRONLY);
        dup2(1,fd1);
        dup2(fd,1);
        close(fd);
        execvp(arg[0],arg);
        dup2(fd1,1);
        break;
    case APPEND:
        fd=open(filename,O_RDONLY|O_APPEND);
        dup2(0,fd1);
        dup2(fd,0);
        close(fd);
        execvp(arg[0],arg);
        dup2(fd1,0);
        break;
    }
}

int pipeline(char **argv,int pipe_num,int *index)
{
    int p[2],count=0;
    pid_t pid;
    int fd_in=0;
    while(count<=pipe_num){
        pipe(p);
        if((pid=fork())==-1){
            exit(EXIT_FAILURE);
        }
        else if(pid==0){
            dup2(fd_in,0); //change the input according to the old one
            if(count<pipe_num){
                dup2(p[1],1);//change the std output to 1
            }
            close(p[0]);
            if(count==0) execvp(argv[0],argv);
            else execvp(argv[index[count-1]+1],argv+(index[count-1]+1));
            exit(EXIT_FAILURE);
        }
        else{
            wait(NULL);
            close(p[1]);//close the output to fd[1]
            fd_in=p[0];//save the input from fd[0]
            count++;
        }
    }
}

int find_pipe(char **command,int status,int *index)
{
    int i,flag=0;
    for(i=0;i<status;i++){
        if(strcmp(command[i],"|")==0){
            command[i]=NULL;
            index[flag]=i;
            flag++;
        }
    }
    return flag;
}

int main(void){
    void * buf;
    int i,j,num,k;
    int status;
    pid_t pid;
    char str[NUM];
    char *argv[NUM];
    int index[NUM];
    list_num=0;
    while(1){
        printf("myshell<<");
        gets(command[list_num]);
        if(strcmp(command[list_num],"exit")==0) break;
        status=mystrtok2(argv,command[list_num]);
        argv[status+1]=NULL;
        //pipe
        int pipe_num=find_pipe(argv,status,index);
        if(pipe_num!=0){
            pipeline(argv,pipe_num,index);
            continue;
        }
        if(strcmp(argv[0],"history")==0){
            num=argv[1][0]-'0';
            printf("list num %d %d\n",list_num,num);
            for (i=list_num;i>=list_num-num+1;i--){
                printf("%s\n",command[i]);
            }
        }
        else if(strcmp(argv[status-1],"&")==0){
            argv[status-1]=NULL;
            if((pid=fork())==0){
                sigaction(SIGINT,SIG_IGN,NULL);
                sigaction(SIGQUIT,SIG_IGN,NULL);
                execvp(argv[0],argv);//****************************************8
            }
        }
        else if(strcmp(argv[0],"cd")==0){
            chdir(argv[1]);
        }
        else {
            if ((pid=fork())!=0) {
            waitpid(pid,&status,0);
            }
            else {
             Accomp(argv,status);
            }
        }
        list_num++;
    }
    return 0;
}
