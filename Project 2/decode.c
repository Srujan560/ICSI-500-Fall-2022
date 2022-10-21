#include <stdio.h>// to print 
#include <unistd.h>// use this for system calls fork and pipe
#include <sys/wait.h>//We this so our parent can wait 
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <stdlib.h>

int main(int arg, char *argc[]){

    char* binaryFile = argc[1];
    char* towrite = argc[2];

    int fd=open(binaryFile,O_RDONLY,0);
    char bin[10000];
    int r = read(fd,bin,10000);
    // printf("\n\n\n\n\nbin: %s",bin);
    // char *dat = bin[x],bin[x+1],bin[x+2],bin[x+3],bin[x+4],bin[x+5],bin[x+6],bin[x+7]
    // int ll = (bin[1]);
    // char aa= ll;
    // printf(" ss %d\nit %c\n",bin[1],aa);
    // exit (0);
    FILE *f = fopen(towrite,"w");
    for(int x=0;x<r;x+=8){
        char tem[8]={bin[x],bin[x+1],bin[x+2],bin[x+3],bin[x+4],bin[x+5],bin[x+6],bin[x+7]}; 
        char *data = tem;
        data[8]='\0';
        // printf("%s",data);
        char c = strtol(data, 0, 2);
        // printf("%c",c);
        fprintf(f,"%c",c);
        // exit(0);
        // printf("x=%d %s\n\n\n",x,data);
    }
     fclose(f);
    close(fd);
        // printf("sise %d\n",r);
    return 0;
}