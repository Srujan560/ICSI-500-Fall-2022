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
    
    for (int x=0;x<r;x+=12){
        // printf("%c ",data[x]);
        char temp[13]={bin[x],bin[x+1],bin[x+2],bin[x+3],bin[x+4],bin[x+5],bin[x+6],bin[x+7],bin[x+8],bin[x+9],bin[x+10],bin[x+11]}; 
        char *some =temp;
        some[12]='\0';
        int countp1 =0,countp2 =0, countp4 =0, countp8 =0;
        // printf("Before changeing error: %s\n",some);
        for(int i=0;i<12;i++){
            // printf("%c",some[i]);
            if(some[i]=='1'){
                if(i==2||i==4||i==6||i==8||i==10)
                    countp1++;
                if(i==2||i==5||i==6||i==9||i==10)
                    countp2++;
                if(i==4||i==5||i==6||i==11)
                    countp4++;
                if(i==8||i==9||i==10||i==11)
                    countp8++;
            }
            
        }
        int errorIndex=0;
        if(countp1 %2 ==1 && some[0]!='1' ||countp1 %2 == 0 && some[0]!='0' )
            errorIndex+=1;
        if(countp2%2==1 && some[1]!='1' || countp2%2==0 && some[1]!='0' )
           errorIndex+=2;
        if(countp4%2==1&& some[3]!='1' || countp4%2==0&& some[3]!='0' )
           errorIndex+=4;
        if(countp8%2==1&&some[7]!='1' ||  countp8%2==0 && some[7]!='0')
            errorIndex+=8;
        
        printf("p1 = %d p2 =%d p4= %d p8=%d\n",countp1,countp2,countp4,countp8);
        printf("Error index[%d] some = %c  and char value: %s\n",errorIndex,some[0],some);
        if(errorIndex!=0){
            errorIndex=errorIndex-1;
            printf("error Handling.c: ERROR ERROR  error detection found at index %d \n",errorIndex);
            if(some[errorIndex]=='1'){
                some[errorIndex]='0';
                printf("error Handling.c: Fixed that bit\n");
            }else{
                some[errorIndex]='1';
                printf("error Handling.c: Fixed that bit\n");
                }
        }
        // printf("soome:%s\n",some);
        char newTempArr[8]= {some[2],some[4],some[5],some[6],some[8],some[9],some[10],some[11]};
        char *newTempStr= newTempArr;
        newTempStr[8]='\0';

        // printf("InputHamming :%s Bits writing: %s  \n",test, newTempStr);
        fprintf(nbin,"%s",newTempStr);
        // printf("\t\t\t****\n\n");
    }
    fclose(nbin);
    return 0;
}