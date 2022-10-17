// #include <stdio.h>
// #include <unistd.h>
//ilbat that will used by main method 
void runEncode(){
    printf("I am here in runEcode in my libary\n");
    char* arr[]={"c",NULL};
    execv("c",arr);
    fprintf(stderr,"Fail to runEncode method From LIBAay\n");
}
/* 
In here we will take in put and out put file
we will read bits than we check 0th index and either we rm it or do nothing 
*/
void decode(char* binaryFile,char* towrite){
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

}
/*
In this method we will take input and output file... we will check the (0 index)8th bit and remove than we know it even
*/

void parityremove(char *fname,char *output){
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
    // printf("All Done\n");
}
/**
 * In here we will take the input file and outfile that we need to write 
*/
void decodeAndUpperCase(char* binaryFile,char* towrite){
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
       
        if(c>='a'&&c<='z'){
            c=c-32;// here we trun char to upeercase 
            
        }
        // printf("%c",c);
        fprintf(f,"%c",c);// than write 
        //  if (c=='\''){printf("OOF %c\n",c);exit(0);} if (c=='\''){printf("OOF\n");exit(0);}//error b/c fancy curve ' is not able to be read
        // exit(0);
        // printf("x=%d %s\n\n\n",x,data);

    }
    fclose(f);// once done close 
    close(fd);
        // printf("sise %d\n",r);

}

void runUppercaseEncode(){
    // printf("I am here in runEcode in my libary\n");
    char* arr[]={"cu",NULL};
    execv("cu",arr);
    fprintf(stderr,"Fail to runUppercaseEncode method From Libary\n");
}

void frameVersion(){
    char *arr[]={"f",NULL};
    execv("f",arr);
    fprintf(stderr,"Fail to run FrameVersion probably need to compile  \n");
}
void deframe(){
    char *arr[]={"d",NULL};
    execv("d",arr);
    fprintf(stderr,"Fail to run deframe probably need to compile  \n");
}
void frameVersionUppercase(){
    char *arr[]={"fu",NULL};
    execv("fu",arr);
    fprintf(stderr,"Fail to run frameVersionUppercase probably need to compile  \n");
}
void deframeUppercase(){
    char *arr[]={"du",NULL};
    execv("du",arr);
    fprintf(stderr,"Fail to run deframe probably need to compile  \n");
}
