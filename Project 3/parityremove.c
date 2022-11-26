#include <stdio.h>// to print 
#include <unistd.h>// use this for system calls fork and pipe
#include <sys/wait.h>//We this so our parent can wait 
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <stdlib.h>

int main(int arg, char *argc[]){

    // printf("inpu = %s and out put =%s and arg=%d\n",argc[1], argc[2], arg);
    char* fname= argc[1];
    char *output =argc[2];
    int fd=open(fname,O_RDONLY,0);
    char bin[10000];
    int r = read(fd,bin,9000);
     if(r==-1){fprintf(stderr,"Was not able to read %s in parityremove\n",fname);}
    // printf("r= %d********************8 %s\n",r,fname);
   
    close(fd);
    FILE *nbin = fopen(output,"w");
    
    for (int x=0;x<r;x+=8){
        // printf("%c ",data[x]);
        char temp[8]={bin[x],bin[x+1],bin[x+2],bin[x+3],bin[x+4],bin[x+5],bin[x+6],bin[x+7]};
        char *some =temp;
        some[8]='\0';
        int count =0;
        for(int i=0;i<8;i++){
            // printf("%c",some[i]);
            if(some[i]=='1'){
                count++;
            }
            
        }
        if (count%2!=0 && some[0]=='1'){
            some[0]='0';
        }
        fprintf(nbin,"%s",some);
    }
    fclose(nbin);
    return 0;
}