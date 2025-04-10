#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sock_fd,client_socket;
    struct sockaddr_in server,client;
    socklen_t len = sizeof(client);
    char buffer[1024];
    //Create
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    //server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
    //bind the socket
    bind(sock_fd,(struct sockaddr*)&server,sizeof(server));
    //listen for incoming connections
    listen(sock_fd,3);
    printf("Server:Waiting for connections\n");
    //accept client connections
    client_socket = accept(sock_fd,(struct sockaddr*)&client,&len);
    //Recieve Data from client
    read(client_socket,buffer,sizeof(buffer));
    printf("Server:Message\t%s\n",buffer);
    send(client_socket,"Hello from Server",17,0);
    close(client_socket);
    close(sock_fd);
}
