#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <stdlib.h>
#include <sys/wait.h>//We this so our parent can wait 


int main(){

    int fk = fork(), wait1=0, wait2=0;
    if(fk<0){fprintf(stderr,"not able to create fork1\n");}// if problem 
    if(fk==0){
        if(!fork()){    // to remove hamming code and fix errors
            char* arr[]={"eh","client.tmp","removeHamming.binary",NULL};
            execv("eh",arr);
            fprintf(stderr,"Fail to to run errorHandling.c method From ClientDecoder\n");
        }
        wait(&wait2);
        printf("Just remove and checked for errorHandling\n");
        int wait3=0;
        if(!fork()){    // to remove priory bits
             char* arr[]={"pr","removeHamming.binary","prRemoved.binary",NULL};
            execv("pr",arr);
            fprintf(stderr,"Fail to to run errorHandling.c method From ClientDecoder\n");
        }
        wait(&wait3);
        printf("Just remove parity bits\n");
        int wait4=0;
        if(!fork()){    // binary to string 
             char* arr[]={"d","prRemoved.binary","results.txt",NULL};
            execv("d",arr);
            fprintf(stderr,"Fail to to run decode.c method From ClientDecoder\n");
        }
        wait(&wait4);
        printf("just decode \n");
    }else{
            // parent 
        printf("running Client Decoder \n");

    } 
    wait(&wait1);



    return 0;
}