#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main (){
    char arr[1000];
    int p2[2];
    if(pipe(p2)==-1){fprintf(stderr,"Was not able to create a pipe in ConsumerProducer.c");return 1;}
    dup2(0,p2[0]);
    int r = read(p2[0],arr,1000);// We know we wrote to Stdin we will just read on Stdout b/c it where we saved it
    // printf("Hello world from Consumer\n***\n%.*s\n****",r,arr);
    int lines=0,words=0;
    for(int x=0;x<r;x++){
        char temp =arr[x];
        
        if(temp==' '){words++;}
        if(temp=='\n'){lines++;}
        if (x==r-1 && temp!=' '){
            words++;// last word to be add
        }

    }
   
    printf("Number of Character %d\nNumber of words =%d\nNumber of lines=%d\n",r,words,lines);
    FILE *fd = fopen("theCount.txt","w");
    // char str[30];
    // sprintf(str,"Number of Character %d\n",r);
    // // write(fd,str,)
    fprintf(fd,"Number of Character %d\nNumber of words =%d\nNumber of lines=%d\n",r,words,lines);
    fclose(fd);
    // printf("%s\n",str);
    // fprintf(0,"Number of Character %d\nNumber of words =%d\nNumber of lines=%d\n",r,words,lines);
    // char ar1[]= {"Character %d\nNumber of words =%d\nNumber of lines=%d\n",r,words,lines};
    int fdcount = open("theCount.txt",O_RDONLY,0);
    dup2(fdcount,0);
    close(fdcount);
    close(p2[0]);
    close(p2[1]);
    return 0;
}