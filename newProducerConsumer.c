#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
    int pid, p1[2],p2[2],stat=0;
    if(pipe(p1)==-1){return -1;}
    if(pipe(p2)==-1){return -1;}
    pid =fork();
    if(pid==0){
        close(p1[0]);
        int fdEdit = open("editSource.txt",O_RDONLY,0);
        // dup2(p1[1],fdEdit);
        // printf("fdEdit%d\n",fdEdit);

        // write(p1[1],"He",2);
        int r=0;
        char editText[1000];
        while((r=read(fdEdit,editText,1000))>0){
            // printf("CHILD: %.*s\n",r,editText);
            write(p1[1],editText,r);
        }
        printf("\t\t********START of  P1[]***************\n");


        close(p1[1]);
        close(fdEdit);
        // now let read from our parent
        /*       reading from our parent      */
        close(p2[1]);
        char parentRes[200];
        int bytesFromParent = read(p2[0],parentRes,200);
        printf("CHILD: From Our parent\n%.*s",bytesFromParent,parentRes);
        close(p2[0]);
        printf("\t\t********END of  P2[]***************\n");


    }else{

        //parent 
        close(p1[1]);
        char childRes[1000];
        int numberOFBytes =read(p1[0],childRes,1000);
        printf("PARENT: from child:\n%.*s\n",numberOFBytes,childRes);
        printf("\t\t********END of  P1[]***************\n");
        int lines=0,words=0;
        for(int x=0;x<numberOFBytes;x++){
            char temp =childRes[x];
            
            if(temp==' '){words++;}
            if(temp=='\n'){lines++;}
            if (x==numberOFBytes-1 && temp!=' '){
                words++;// last word to be add
            }

        }
   
        // printf("Number of Character %d\nNumber of words =%d\nNumber of lines=%d\n",numberOFBytes,words,lines);
        FILE *fd = fopen("theCount.txt","w");
        // char str[30];
        // sprintf(str,"Number of Character %d\n",r);
        // // write(fd,str,)
        fprintf(fd,"Number of Character %d\nNumber of words =%d\nNumber of lines=%d\n",numberOFBytes,words,lines);
        fclose(fd);
        /*      Now let right back to another pipe2[0]                   */
        close(p2[0]);
        int fdEdit = open("theCount.txt",O_RDONLY,0);
            int r=0;
            char editText[200];
            while((r=read(fdEdit,editText,200))>0){
                write(p2[1],editText,r);
            }
        close(p2[1]);
        printf("\t\t********START of  P2[]***************\n");



    }
    wait(&stat);
    
    
    
    
    return 0;
}