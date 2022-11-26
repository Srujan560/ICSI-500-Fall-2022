#include <stdio.h> 
#include <pthread.h> // must use -pthread
#include <unistd.h> // system call
#include <stdlib.h>
#include <fcntl.h> // "r", "a" to read files
#include <sys/stat.h>
#include <string.h> // this for strlen() and strncpy
#include <ctype.h> // this for toUpper()
#include <semaphore.h> // for semaphore
// #include <limits.h> // this for PATH_MAX... to get our dir

sem_t mutex , mutex2, mutex3, mutex4, mutex5, mutex6, mutex7;
void *charA(void*);
void *charE(void*);
void *charI(void*);
void *charO(void*);
void *charU(void*);
void *digit(void*);
void *writer(void*);
int numberOfLines=0, numberChars=0,totalChar=0;
char buffer[10025],arr1[8];

void *charA(void* arg){
    sem_wait(&mutex);
    // printf("I am here In Char A\n");
    for(int x=0;x<numberChars;x+=7){
        strncpy(arr1,&buffer[x],7);
        arr1[7]='\0';

        for(int i=0;i<7;i++){
            if(arr1[i]=='a')
                arr1[i]='A';
            
        }
        printf("arr1: %s\n",arr1);
        // let charE run
        sem_post(&mutex2);
        // stop here
        sem_wait(&mutex);



    }



}
char arr2[8];
void *charE(void* arg){
    int run=0;
    while(run<=numberChars){
        //wait for CharA to put in arr1
        sem_wait(&mutex2);
        // printf("I am here In Char E while loop\n");
        for(int i=0;i<7;i++){
            if(arr1[i]=='e')
                arr2[i]='E';
            else
                arr2[i]=arr1[i];
            
        }

        run+=7;  //this will stop our loop'
        //let CharI start
        sem_post(&mutex3);
        // sem_post(&mutex); // do 
        //stop here
        printf("Arr2 :%s\n",arr2);

       

    }
}
char arr3[8];
void *charI(void* arg){
    int run=0;
    
    while(run<=numberChars){
        // wait for CharE to put in array
        sem_wait(&mutex3);
        // printf("I am here In Char I\n");
        for(int i=0;i<7;i++){
            if(arr2[i]=='i')
                arr3[i]='I';
            else
                arr3[i]=arr2[i];
            
        }
        run+=7;  //this will stop our loop
        sem_post(&mutex4);  // Let CharO run
        // sem_post(&mutex2); // do 
        printf("Arr3: %s\n",arr3);
    }
}
char arr4[8];
void *charO(void* arg){
    int run=0;
    
    while(run<=numberChars){
        sem_wait(&mutex4);
        //  printf("I am here In Char O\n");
        for(int i=0;i<7;i++){
            if(arr3[i]=='o')
                arr4[i]='O';
            else
                arr4[i]=arr3[i];
            
        }
        run+=7; //this will stop our loop
        sem_post(&mutex5); // let charU run
        // sem_post(&mutex3);
        printf("Arr4: %s\n",arr4);

    }
}
char arr5[8];
void *charU(void* arg){
    int run=0;
    
    while(run<=numberChars){
        sem_wait(&mutex5);
        // printf("I am here In Char U\n");
        for(int i=0;i<7;i++){
            if(arr4[i]=='u')
                arr5[i]='U';
            else
                arr5[i]=arr4[i];
            
        }
        run+=7;  //this will stop our loop
        sem_post(&mutex6);
        // sem_post(&mutex4); // do
        printf("Arr5: %s",arr5);

    }
}
int numberOfDigits=0;
void *digit(void* arg){
    int run=0;
    
    while(run<=numberChars){
        sem_wait(&mutex6);
        // printf("I am here in the count\n");
        for(int i=0;i<7;i++){
            if(arr5[i]>='0' && arr5[i]<='9')
                numberOfDigits++;
            
        }
        run+=7;  //this will stop our loop
        sem_post(&mutex7);
        // sem_post(&mutex);
        // sem_post(&mutex5);

    }
}

void *writer(void *arg){
    int run=0, count=0;
    char finallyArr[totalChar];
    while(run<=numberChars){
        sem_wait(&mutex7);
        // printf("I am here in Writer\n");
        for(int i=0;i<7;i++){
            finallyArr[count]=arr5[i];
            count++;
            
        }

        run+=7;  //this will stop our loop
        // sem_post(&mutex6);
        printf("Writer has : %s\n", finallyArr);
        printf("ok what is my run= %d and numberChars = %d and number of digits=%d\n", run,numberChars,numberOfDigits);
        sem_post(&mutex);


    }
    

    FILE *nbin = fopen("Pthread.tmp","w");
    char *tempStr =finallyArr;
    fprintf(nbin,"%s",tempStr);
    fprintf(nbin,"\nNumber of digits counted was %d\n", numberOfDigits);
    fclose(nbin);

}

void countLoopTurns(char *filename){
    FILE *filepointer = fopen(filename,"r");
    char *temText=""; 
    size_t len =0;
    while(getline(&temText,&len,filepointer)!=-1)
		numberOfLines++;
	fclose(filepointer);
}

int main(){

    countLoopTurns("resultsServer.txt");
    printf("number of lines %d\n",numberOfLines);
    int fd =open("resultsServer.txt",O_RDONLY,0);
    int r = read(fd,buffer,10025);
    totalChar=r;
    if(r%7==0){
        numberChars=r;

    }else{
        numberChars=r+1;

    }

    printf("Number of bites I just read: %d\n",r);
    // charA(NULL);


    // semaphore
	sem_init(&mutex, 0, 1);
	sem_init(&mutex2, 0, 0);
	sem_init(&mutex3, 0, 0);
	sem_init(&mutex4, 0, 0);
    sem_init(&mutex5, 0, 0);
    sem_init(&mutex6, 0, 0);
    sem_init(&mutex7, 0, 0);

    pthread_t th1, th2, th3, th4, th5, th6, th7;

    pthread_create(&th1, NULL,charA, NULL);
    pthread_create(&th2, NULL,charE, NULL);
    pthread_create(&th3, NULL,charI, NULL);
    pthread_create(&th4, NULL,charO, NULL);
    pthread_create(&th5, NULL,charU, NULL);
    pthread_create(&th6, NULL,digit, NULL);
    pthread_create(&th7, NULL,writer, NULL);


    // wait for the pthread to end 
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	pthread_join(th3,NULL);
	pthread_join(th4,NULL);
    pthread_join(th5,NULL);
	pthread_join(th6,NULL);
	pthread_join(th7,NULL);

    // remove semaphore
	sem_destroy(&mutex);
	sem_destroy(&mutex2);
	sem_destroy(&mutex3);
	sem_destroy(&mutex4);
    sem_destroy(&mutex5);
    sem_destroy(&mutex6);
    sem_destroy(&mutex7);

    return 0;

}