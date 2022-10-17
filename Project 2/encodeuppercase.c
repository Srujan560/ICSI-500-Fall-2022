#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <stdlib.h>


void parity(){
    int fd=open("binaryuppercase.chck",O_RDONLY,0);
    char bin[10000];
    int r = read(fd,bin,9000);
    close(fd);
    FILE *nbin = fopen("binaryuppercase.chck","w");
    
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
        if (count%2==0){
            some[0]='1';
        }
        fprintf(nbin,"%s",some);

            // printf("%d\n",count);
            // printf("%s ",some);
           

        // printf("%s ",some);
    }
    fclose(nbin);
    // printf("All Done\n");
}

int main(){
    int fd=open("uppercase.outf",O_RDONLY,0);
    FILE *bin = fopen("binaryuppercase.chck","w");

    int r=0;
        char editText[1000];
        while((r=read(fd,editText,1000))>0){
           
            for(int x=0;x<r;x++){
                
                unsigned char c = editText[x];
                for (int i=7;i>=0;i--){
                    
                    fprintf(bin,"%c",( c >> i ) & 1 ? '1' : '0');

                }
            } 
            
        }
        close(fd);
        fclose(bin);
        parity();
        // decode();
}