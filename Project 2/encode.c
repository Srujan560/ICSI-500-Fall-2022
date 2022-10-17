#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <stdlib.h>

// in here check add our odd parity bit 
void parity(){
    int fd=open("binary.binf",O_RDONLY,0);
    char bin[10000];
    int r = read(fd,bin,9000);
    close(fd);
    FILE *nbin = fopen("binary.binf","w");
    
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
}

int main(){
    int fd=open("user.inpf",O_RDONLY,0);
    FILE *bin = fopen("binary.binf","w");

    int r=0;
        char editText[1000];
        while((r=read(fd,editText,1000))>0){
            // printf("Binary: %.*s\n",r,editText);
            //convert to bin
            // char *c=("%.s",r,editText);
            for(int x=0;x<r;x++){
                
                unsigned char c = editText[x];
                //  unsigned char temp[8];
                for (int i=7;i>=0;i--){
                    // printf("%d",( c >> i ) & 1 ? 1 : 0);
                    // ( c >> i ) & 1 ? '1' : '0';
                    fprintf(bin,"%c",( c >> i ) & 1 ? '1' : '0');


                }
                // temp[8]='\0';
                // printf("%s\n",temp);
                
               
                

               
            }
            
            
            
        }
        // close everything once done 
        close(fd);
        fclose(bin);
        parity();
        
        // decode();
}