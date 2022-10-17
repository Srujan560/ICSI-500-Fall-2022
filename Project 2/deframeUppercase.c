#include <stdio.h>
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <unistd.h>// open()
#include <string.h>// stringcat string cpy
#include <stdlib.h>

int main(){
    printf("running Deframe  for .chck\n");
     char arr[10000];
     int fd = open("pread2.tmp",O_RDONLY,0);
     int r = read(fd,arr,10000);
     close(fd);

    //  printf("I read r %d\n",r);
    FILE *fd2 = fopen("deframedUppercase.tmp","w");
    char syn[]="00010110";
    int check=0,check2=0;
    for (int  i = 0; i < r; i+=8){
        char checkSYN[9]= {arr[i],arr[i+1],arr[i+2],arr[i+3],arr[i+4],arr[i+5],arr[i+6],arr[i+7]};
        // printf("Checking my %s\n",checkSYN);
        //let check the frist and sencond is 22
        if(check2==0){
            if(check==0){
            for (int k=0;k<8;k++){
                if (syn[k]==checkSYN[k]){check=1;}
                else {check=0;break;}
            }
            }
            else{
            
            if(check==1){
                check=0;
                for (int k=0;k<8;k++){
                if (syn[k]==checkSYN[k]){check2=1;}
                else {check2=0;break;}
                }
            }
            }
        }else{
            // let turn binary to int
            char*temStrInt = checkSYN;
            int byNum = atoi(temStrInt), decimal_num=0,base=1,rem;
            // printf(" num = %d\n",byNum);
            while(byNum>0){
                rem=byNum%10;
                decimal_num=decimal_num+rem*base;
                byNum=byNum/10;
                base=base*2;
            }
            // if(decimal_num!=32)  
            // printf(" INT = %d and check2=%d\n",decimal_num,check2);
            i=i+8;
            // printf("i= %d before\n",i);
            int tempIndex=i+(8*decimal_num),strIndex=0;
            char tempStrArray[8*decimal_num +2];
            for( int x=i;x<tempIndex;x++){
                // fprintf(fd2,"%c",arr[x]);
                tempStrArray[strIndex]=arr[x];
                strIndex++;
            }
            char* tempStrWrite=tempStrArray;
            tempStrWrite[strIndex]='\0';
            // printf("strArrAy = %s\n",tempStrArray);
            fprintf(fd2,"%s",tempStrWrite);
            // printf("str = %s\n",tempStrWrite);
            i=tempIndex-8;
            // printf("i= %d strIndex= %d and 8*dec =%d and tempInd= %d\n",i,strIndex,8*decimal_num,tempIndex);
            // if(checkSYN[4]=='1'){
            //     i=i+8;
            //     int tempIndex=i+(8*8),strIndex=0;
            //     char tempStrArray[8*8 +1];
            //     for( int x=i;x<tempIndex;x++){
            //         // fprintf(fd2,"%c",arr[x]);
            //         tempStrArray[strIndex]=arr[x];
            //         strIndex++;
            //     }
            //     char* tempStrWrite=tempStrArray;
            //     fprintf(fd2,"%s",tempStrWrite);
            //     i=tempIndex;
            // }else{
            //     // printf("Am here?\n");
            //     i=i+8;
            //     char tempStrArray[8*32 +1];
            //     int tempIndex=i+(8*32),strIndex=0;
            //     for( int x=i;x<tempIndex;x++){
            //         // fprintf(fd2,"%c",arr[x]);
            //         // printf("%c",arr[x]);
            //         tempStrArray[strIndex]=arr[x];
            //         strIndex++;

            //     }
            //     char* tempStrWrite=tempStrArray;
            //     fprintf(fd2,"%s",tempStrWrite);
            //     i=tempIndex;
            // }
            check2=0;
            
        }
        // exit(0);

    }
    fclose(fd2);

    // int fd3  open("pread.tmp",O_RDONLY,0);
    //  int yy = read(fd,arr,10000);
    // printf("I am done\n");
    


    return 0;
}