#include <stdio.h>
#include <fcntl.h>// for reading "RDONLY WRONLY..."
#include <unistd.h>
#include <string.h> // strcpy and strcat
#include <stdlib.h>//opne()


int main(){
    printf("Adding Frames to .chck\n");
    int fd = open("binaryuppercase.chck",O_RDONLY,0);
    char arr[10000];
    int r =read(fd,arr,9000);
    close(fd);
    FILE *fd2 = fopen("binaryuppercase.chck","w");
    int count = 0;
    // char *dd=(char*)malloc(1000);
    for (int x=0; x<r;x+=8){
        // char temp[8]={arr[x],arr[x+1],arr[x+2],arr[x+3],arr[x+4],arr[x+5],arr[x+6],arr[x+7]};
        // char *some =temp;
        // some[8]='\0';
        count++;
        // char *tempStr = (char *)malloc(1+strlen(dd)+strlen(some));
        // strcpy(tempStr,dd);
        // strcpy(tempStr,some);
        // free(dd);
        // dd= (char*)malloc(strlen(tempStr));
        // strcpy(dd,tempStr);
        // // free(tempStr);
        // printf("my dd is %s\n",dd);

        //let make sure that if have count of 32 or we end of our binary 
        if (count==32||(x+7)==r-1){
            int tempInt =x- (count -1)*8;
            // printf("Is not 32 from framing.c %d\n",count);
            // if (count!=32){printf("Is not 32 from framing.c %d\n\n\n\n\n\n",count);exit(1);}
            // printf("tempInt = %d and r= %d\n",tempInt, r);
            // printf("x-32 = %d count = %d and x= %d and x+8 = %d \n",x-tempIntk,count,x,x+7);
            // exit(0);
            // if(x+7==r-1){
            //     printf("r = %d x+7 = %d and val= %c\n",r-1,,arr[x+7]);
            // }
            // base on the array make sises 
            char tempCharArr[(count)*8 ];
            for (int y=0; y<sizeof(tempCharArr);y++){
                tempCharArr[y]=arr[tempInt+y];
            }
            // printf("val= %s\n",tempCharArr);
            char binaryNum[9]; // Assuming 32 bit integer.
            for (int z=0;z<8;z++){
                binaryNum[z]='0';
                // printf("z=%d ch=%c\n",z,binaryNum[z]);
                // printf("%s\n",binaryNum);
            }
            binaryNum[8]='\0';

            // printf("str a a a %s\n",binaryNum);
            // exit(0);
            
            int i=7;
            int num=count;
            while (num > 0) {
                if(num%2==1)
                    binaryNum[i--]='1';
                else
                    i--;
                num /= 2;
            }
            
            if (count!=32){

                // printf("\n\nmy binary str =%s count=%d \n\n",binaryNum,count);
            }
            

            // printf("str %s\n",binaryNum);
            // now let write everything on the string to our file
            char *SYN2= "0001011000010110";
            char *binChar = binaryNum;
            char *newFrame = (char *)malloc(1+strlen(SYN2)+strlen(binChar));//so exact bits to write
            strcpy(newFrame,SYN2);// frist add SYN22
            strcat(newFrame,binChar);// how bits we read
            char *tempPase=tempCharArr;// than our ch in binary
            fprintf(fd2,"%s%s",newFrame,tempPase);
            // exit(0);
            
            // let rest counter
            count=0;
        }
        
    }
    // once done let close
    fclose(fd2);
    // char *some = "Hello";
    // char *another = "2020202020 ";
    // char* a=(char*)malloc(1+strlen(another)+ strlen(another));
    // strcpy(a, another);
    // strcat(a,some);


    // printf("Another = %s\n",a);
return 0;

}