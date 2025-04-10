#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sock_fd,client_socket;
    struct sockaddr_in server;
    char buffer[1024]={"Hello from Client"};
    //Create
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    //server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8080);
    //connect to server
    connect(sock_fd,(struct sockaddr*)&server,sizeof(server));
    send(sock_fd,buffer,strlen(buffer),0);
    read(sock_fd,buffer,sizeof(buffer));
    printf("Client:Response\t%s\n",buffer);
    close(sock_fd);
}
