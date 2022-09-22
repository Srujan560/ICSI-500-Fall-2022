#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
// #include 

int main (){
    // printf("Hello world\n");
    int pid, p1[2],p2[2],stat=0;
    if(pipe(p1)==-1){return -1;}
    if(pipe(p2)==-1){return -1;}
    pid =fork();
    if(pid==0){
        printf("I am the child\n");
        char* arr[] ={"c",NULL};
        int fdEdit = open("editSource.txt",O_RDONLY,0);
        
        close(p1[0]);//read
        // close(p2[1]);
        
        dup2(fdEdit,0);
        dup2(p1[1],1);// but we want to read this from consumerProducer.c so we put our hole file in pipe 1, so we are writing to other pipe
        // dup2(p2[0],0);
        close(p1[1]);//write
        close(p2[0]);
        close(fdEdit);
        execv("c",arr);
        fprintf(stderr,"failed to run\n");// to print out error 
        
    }else{
        char input[1000];
        // int byteRead =read(0,input,1000);
        printf("I am the parent\n");
        close(p1[1]);//we want to read not write
        // close(p2[0]);
        // close(p2[1]);
        
        // Let read from our pipe which we know it file descriptor 0 so we will read
        dup2(p1[0],0);//we are reading form the other pipe
        
        int byteRead =read(p1[0],input,1000);// let read our pipe now 
        // write(1,input,byteRead);
        printf("I just read from consumer\n%.*s",byteRead,input);
       

        }
    wait(&stat);//let wait till our child is done so we do not create zombie

    

}