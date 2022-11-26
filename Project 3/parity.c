
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <stdlib.h>
int main(int arg, char *argc[]){
    char* towrite= argc[1];
    int fd=open(towrite,O_RDONLY,0);
    char bin[10000];
    int r = read(fd,bin,9000);
    close(fd);
    FILE *nbin = fopen(towrite,"w");
    
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
        if (count%2==0){// if even let just add but 
            some[0]='1';
        }
        fprintf(nbin,"%s",some);

            // printf("%d\n",count);
            // printf("%s ",some);
           

        // printf("%s ",some);
    }
    fclose(nbin);
    // printf("All Done\n");
    return 0;
}