#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <stdlib.h>
#include <sys/wait.h>//We this so our parent can wait 


int main(){

    int fk = fork(), wait1=0, wait2=0;
    if(fk<0){fprintf(stderr,"not able to create fork1\n");}// if problem 
    if(fk==0){
        if(!fork()){
            char* arr[]={"eh","server.tmp","removeHammingServer.binary",NULL};
            execv("eh",arr);
            fprintf(stderr,"Fail to to run errorHandling.c method From ServerDecoder\n");
        }
        wait(&wait2);
        printf("Just remove and checked for errorHandling\n");
        int wait3=0;
        if(!fork()){
             char* arr[]={"pr","removeHammingServer.binary","prRemovedServer.binary",NULL};
            execv("pr",arr);
            fprintf(stderr,"Fail to to run errorHandling.c method From ServerDecoder\n");
        }
        wait(&wait3);
        printf("Just remove parity bits\n");
        int wait4=0;
        if(!fork()){
             char* arr[]={"d","prRemovedServer.binary","resultsServer.txt",NULL};
            execv("d",arr);
            fprintf(stderr,"Fail to to run decode.c method From ServerDecoder\n");
        }
        wait(&wait4);
        printf("just decode \n");
    }else{
        printf("running Server Decoder \n");

    } 
    wait(&wait1);



    return 0;
}