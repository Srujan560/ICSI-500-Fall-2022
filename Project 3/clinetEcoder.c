#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <stdlib.h>
#include <sys/wait.h>//We this so our parent can wait 


int main(){

    int fk = fork(), wait1=0, wait2=0;
    if(fk<0){fprintf(stderr,"not able to create fork1\n");}// if problem 

    if(fk==0){
        // int fk2=fork();
        // if(fk2<0){fprintf(stderr,"not able to create fork2\n");}// if problem 
        int wait2=0;
        if(!fork()){
            char* arr[]={"e","intext.txt","output.binary",NULL};
            execv("e",arr);
            fprintf(stderr,"Fail to Encode method From ClientEcode\n");
        }
        wait(&wait2);
        int wait3=0;
        printf("Just turn into binary file\n");
        if(!fork()){
            char* arr[]={"p","output.binary",NULL};
            execv("p",arr);
            fprintf(stderr,"Fail to to run parity method From ClientEcode\n");
        }
        wait(&wait3);
        int wait4=0;
        printf("Just turn into parity bit \n");        
        if(!fork()){
            char* arr[]={"h","output.binary","hammingOutput.binary",NULL};
            execv("h",arr);
            fprintf(stderr,"Fail to to run parity method From ClientEcode\n");
        }
        wait(&wait4);  
        // int wait5=0;
        // if(!fork()){
        //     printf("my soncodne\n");
        // }
        // wait(&wait5);
        
        printf("Just Add hamming code \n");

    }else{
        printf("running client Encoder\n");

    }

    
    wait(&wait1);
    return 0;
   
}