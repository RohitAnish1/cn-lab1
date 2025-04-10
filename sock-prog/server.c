#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd,newsock;
    struct sockaddr_in server,client;
    socklen_t len = sizeof(client);
    char buffer[1024];
    //Create Socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    //Configure server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
    //Bind the socket
    bind(sockfd,(struct sockaddr*)&server,sizeof(server));
    //Start listening for incoming connections
    listen(sockfd,5);
    printf("Waiting for connections:\n");
    //accept incoming connections
    newsock = accept(sockfd,(struct sockaddr*)&client,&len);
    //Read data from client
    read(newsock,buffer,sizeof(buffer));
    printf("Message:%s\n",buffer);
    send(newsock,"Hello from Server",17,0);
    close(newsock);
    close(sockfd);
    return 0;
}
