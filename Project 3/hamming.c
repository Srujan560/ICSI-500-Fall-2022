#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <stdlib.h>

int main(int arg, char *argc[]){
    char* inputFile= argc[1];
    char *outputFile =argc[2];

    int fd=open(inputFile,O_RDONLY,0);
    char bin[10000];
    int r = read(fd,bin,9000);
    close(fd);
    FILE *nbin = fopen(outputFile,"w");

    //choose a number from 0-7:
    int errorChooseIndex = 2;
    //make sure the choose is with the range of user input text
    int repeatedAttack = 3;

    // // here we pick our bits go with our array after adding hamming code 
    if(0<=errorChooseIndex && errorChooseIndex<=7){
        if(errorChooseIndex==0)
            errorChooseIndex=2;
        else if (errorChooseIndex==1)
            errorChooseIndex=4;
        else if (errorChooseIndex==2)
            errorChooseIndex=5;
        else if (errorChooseIndex==3)
            errorChooseIndex=6;
        else if (errorChooseIndex==4)
            errorChooseIndex=8;
        else if (errorChooseIndex==5)
            errorChooseIndex=9;
        else if (errorChooseIndex==6)
            errorChooseIndex=10;
        else if (errorChooseIndex==7)
            errorChooseIndex=11;   
    }else{
        printf("ERROR: ERROR you number is out of index pick or run again with lower number 0-7 \nDEFAULT attack on bits will go head\n\t\t****\n");
        

    }
    
    for (int x=0;x<r;x+=8){
        // printf("%c ",data[x]);
        char temp[9]={bin[x],bin[x+1],bin[x+2],bin[x+3],bin[x+4],bin[x+5],bin[x+6],bin[x+7]};
        char *some =temp;
        some[8]='\0';
        int countp1 =0,countp2 =0, countp4 =0, countp8 =0;
        char temp2[12]={'0','0',some[0],'0',some[1],some[2], some[3],'0', some[4],some[5],some[6],some[7]};

        for(int i=0;i<8;i++){
            // printf("%c",some[i]);
            if(some[i]=='1'){
                if(i==0||i==1||i==3||i==4||i==6)
                    countp1++;
                if(i==0||i==2||i==3||i==5||i==6)
                    countp2++;
                if(i==1||i==2||i==3||i==7)
                    countp4++;
                if(i==4||i==5||i==6||i==7)
                    countp8++;
            }
            
        }
        // printf("p1 = %d p2 =%d p4= %d p8=%d\n",countp1,countp2,countp4,countp8);
        if(countp1%2!=0)
            temp2[0]='1';
        if(countp2%2!=0)
            temp2[1]='1';
        if(countp4%2!=0)
            temp2[3]='1';
        if(countp8%2!=0)
            temp2[7]='1';

        // add error after calculating hamming code 
        if(repeatedAttack!=0){
            

            // here we flip the bits to make an error 
            if(temp2[errorChooseIndex]=='1')
                temp2[errorChooseIndex]='0';
            else
                temp2[errorChooseIndex]='1';

    
            repeatedAttack--;// stop error
            printf("adding an error bit to mess with bits bit number is %d\n",repeatedAttack);
        }

        char *finalStr = temp2;
        finalStr[12]='\0'; 
        printf("HammingOuput: %s some: %s\n",finalStr,some);
        fprintf(nbin,"%s",finalStr);

            // printf("%d\n",count);
            // printf("%s ",some);
           

        // printf("%s ",some);
    }
    fclose(nbin);
    // printf("All DOne\n");
    return 0;
    
}