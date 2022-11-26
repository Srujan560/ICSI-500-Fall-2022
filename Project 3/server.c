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
    

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    char buffer[10025];
    int n;

    server_sock = socket(AF_INET, SOCK_STREAM,0);
    if(server_sock <0){
        perror("[-]Socket Error\n");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");
    memset(&server_addr,'\0', sizeof(server_addr));     // set up
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=port;
    server_addr.sin_addr.s_addr = inet_addr(ip);


    n=bind(server_sock,(struct sockaddr*)&server_addr, sizeof(server_addr));

    if(n<0){
        perror("[-]Bind error");
        exit(1);
    }
    printf("[+] Bind to port number: %d\n",port);

    listen(server_sock, 5);
    printf("[+] Listing ....\n");


    while(1){
        addr_size = sizeof (client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr,&addr_size );
        printf("[+]Nice Client has been successfully connected \n");

        // listing
         bzero(buffer, 10025);
         recv(client_sock,buffer,sizeof(buffer),0);
        //  printf("Client:%s\n",buffer);
        FILE *nbin = fopen("server.tmp","w");
        char *tempStr =buffer;
        fprintf(nbin,"%s",tempStr);
        fclose(nbin);

        int wait1=0;
        if(!fork()){
            char* arr[]={"sd",NULL};
            execv("sd",arr);
            fprintf(stderr,"Fail to to run ServerDecoder from Server.c\n");
        }
        wait(&wait1);
        printf("Server decoder is done about send run pthreads to service\n");

        // sending a message
         bzero(buffer, 10025);
         strcpy(buffer, "Hi this SERVER :P \n");
         printf("Server: %s\n",buffer);
         send(client_sock,buffer,strlen(buffer),0);
        
        // closing client socket 
         close(client_sock);
         printf("[+]Client disconnected \n\n");
    }



    return 0;    
}


// TCP IMPLEMENTATION src="https://www.google.com/search?q=socket+programming+in+c&sxsrf=ALiCzsbo-pPGZQEi5f4vkAF7-8R7olgZaQ:1669210756989&source=lnms&tbm=vid&sa=X&ved=2ahUKEwiU1ObRtsT7AhVbE1kFHYgQC9sQ_AUoAXoECAIQAw&biw=1536&bih=746&dpr=1.25#fpstate=ive&vld=cid:00867885,vid:io2G2yW1Qk8"