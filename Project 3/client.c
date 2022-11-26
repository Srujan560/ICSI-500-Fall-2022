#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/wait.h>//We this so our parent can wait
#include <fcntl.h>// for reading "RDONLY WRONLY..."




int main(){
    char *ip = "127.0.0.1";
    int port =3001;
   

    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[10025];
    int n;

    sock = socket(AF_INET, SOCK_STREAM,0);
    if(sock <0){
        perror("[-]SOcker Error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");
    memset(&addr,'\0', sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=port;
    addr.sin_addr.s_addr = inet_addr(ip);


    connect(sock,(struct sockaddr*)&addr, sizeof(addr));
    printf("[*]Connected to the server\n");


    // bzero(buffer, 1025);
    // strcpy(buffer, "Hello world\n.");
    // printf("Client: %s\n",buffer);
    // send(sock,buffer,strlen(buffer),0);
    int wait1=0;
    if(!fork()){
        char* arr[]={"ce",NULL};
        execv("ce",arr);
        fprintf(stderr,"Fail to to run ClientEcode from Client.c\n");
    }
    wait(&wait1);
    printf("Client Encode done about send packet\n");
    
    //send the file
    int fd=open("hammingOutput.binary",O_RDONLY,0);
    int r = read(fd,buffer,10025);
    close(fd);
    if(r==-1){fprintf(stderr,"Was not able to read hammingOutput.binary in client.c\n");}
    send(sock,buffer,r,0);
    printf("Just Send the bits to TCP server\n");



    bzero(buffer, 10025);
    recv(sock,buffer,sizeof(buffer),0);
    printf("Server:%s\n",buffer);

    // safe the data in file;
    FILE *nbin = fopen("client.tmp","w");
    char *tempStr =buffer;
    fprintf(nbin,"%s",tempStr);
    fclose(nbin);

    int wait2=0;
    if(!fork()){
        char* arr[]={"cd",NULL};
        execv("cd",arr);
        fprintf(stderr,"Fail to to run ClientEcode from Client.c\n");
    }
    wait(&wait2);

    close(sock);
    printf("Disconnected from the server\n\n\n");

    printf("Nice! Got everything Please take look at  result.txt\n");



    return 0;

}