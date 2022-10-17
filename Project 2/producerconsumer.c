#include <stdio.h>// to print 
#include <unistd.h>// use this for system calls fork and pipe
#include <sys/wait.h>//We this so our parent can wait 
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <stdlib.h>
#include "encdec.h"
// this is the main class the user need to run before run please go check out encdech.h libary
int main(){
    int p[2], p2[2], fk, stat=0, statFrameWaiter=0, statDefrmae=0, statdu=0;
    // create pipe, fork, and wait for each fork we will create 
    if(pipe(p)==-1){fprintf(stderr,"pipe 1 was not able to be created\n"); return -1;}
    if(pipe(p2)==-1){fprintf(stderr,"pipe 2 was not able to be created\n"); return -1;}
    fk=fork();
    //after make sure all the pipe are made than fork 
    if(fk<0){fprintf(stderr,"not able to create fork1\n");}// if problme 
    if(fk==0){
        close(p[0]);
        close(p2[1]);
        // let close what do not use
        printf("I am the child (Producer)\n");
        int fk2= fork();
        // let run encode from user input file they give
        if(fk2==0){
            runEncode();
        }

        int fkFramer=fork();
        // than we will get our binary file now let add the framer version and add parity bit
        if(fkFramer==0){
            frameVersion();
        }

        // runEncode();
        // printf("I am here2\n");
        // now let write to the pipe
        int mybinf = open("binary.binf",O_RDONLY,0);
        char arr[10000];
        int readBinf=0;
        while((readBinf=read(mybinf,arr,10000))!=0){
            write(p[1],arr,readBinf);
            // printf("PRODUCER d=%d\n",readBinf);
        }
        close(mybinf);
        close(p[1]);
        // now we are done with pipe one we closed it d
        // exit(1);
        char arr2[10000];
        printf("[From Producer]: Waiting\n");
        // no we wait will get something form parent
        FILE *fdchckTemp = fopen("pread2.tmp","w");
        int newr =0;
        while((newr=read(p2[0],arr2,10000))!=0){
            char *tempStrWriter = arr2;
            fprintf(fdchckTemp,"%s",tempStrWriter);
        }
        close(p2[0]);
        fclose(fdchckTemp);
        //once we something form the parent than we will put all output in temp files than read from thoes temp files
        // printf("What am I reading from pipe 2 \t%.*s r=%d\n",newr,arr2,newr);
        // char* newbin=arr2;
        printf("[From Producer]: just got all Encoded  + parity + frame version of .outf \n");
        int fkdu=fork(),st=0;
        // let remove defreame
        if(fkdu==0){
            deframeUppercase();
        }
        wait(&st);
       // let remove the parity bit 
        parityremove("deframedUppercase.tmp","p_removed.outf");
        // than give the user .doen file
        decode("p_removed.outf","user.done");

    }else{
        close(p[1]);
        close(p2[0]);
        printf("I am here I am the parent (Consumer)\n");
        // let read form the child make sure we have wirte and keep copy of all the tings we just read
        FILE *fdbinfTemp = fopen("pread.tmp","w");
        char arrBinf[10000];
        int firstRead =0;
        
        while((firstRead=read(p[0],arrBinf,10000))!=0){
            // printf("How may bty %d\n", firstRead);
            char *tempStrWriter = arrBinf; 
            fprintf(fdbinfTemp,"%s",tempStrWriter);
        }
        
        printf("[From Consumer]: Just got all Encoded + parity + frame version of .inpf from Producer pipe 1\n");
       
       fclose(fdbinfTemp);
       //once read let close all things we will not use anymore
        // exit(1);
       int deframefk=fork(),statwat=0;
       if (deframefk==0){
            deframe();
       }
    //    printf("STILL Here\n");
       wait(&statwat);
       // remove our frmaes 
       
        // remobe our pritory bit 
        parityremove("deframed.tmp","bremoved.binf");
        // decode("bremoved.binf","out.test");
        decodeAndUpperCase("bremoved.binf", "uppercase.outf");//once decode we can now trun into char

        int fk2=fork(),sta2=0;
        
        // now let encode our all upercase letters 
        if(fk2==0){
            runUppercaseEncode();
        }
        wait(&sta2);
        // printf("I am here+++\n");
        // int fdout=open("uppercase.outf",O_RDONLY,0);
        // int r=0;
        // char text[200];
        // while((r=read(fdout,text,200))>0){
        //     write(p2[1],text,r);
        // }
        // printf("I am here****\n");
        // now we can put in frames and add priory bit
        int fkuppercasefrmaer=fork(),statfrmaerUpper=0;
        if(fkuppercasefrmaer==0){
            frameVersionUppercase();
        }
        wait(&statfrmaerUpper);
        // now once we have our add our frame 
        char arr4Uppercase[10000];
        int mychck= open("binaryuppercase.chck",O_RDONLY,0);
        int rFramer=0;
        // we go write to p2
        while((rFramer=read(mychck,arr4Uppercase,10000))!=0){
            write(p2[1],arr4Uppercase,10000);
        }
        close(mychck);
        close(p2[1]);
        // than close everything
        // write(p2[1],"binaryuppercase.chck",30);
        // printf("I am here/////\n");

    }
    wait(&stat);
    wait(&statFrameWaiter);
    wait(&statDefrmae);
    wait(&statdu);

    

    
   
    

    return 0;

}