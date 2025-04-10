#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sock_fd,new_socket;
    struct sockaddr_in server,client;
    socklen_t len = sizeof(client);
    char buffer[1024];
    //create socket
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd == 0){
        perror("Socket Creation Failed");
        exit(EXIT_FAILURE);
    }
    //server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
    //bind the socket
    bind(sock_fd,(struct sockaddr*)&server,sizeof(server));
    listen(sock_fd,5);
    printf("Waiting for connections\n");
    new_socket = accept(sock_fd,(struct sockaddr*)&client,&len);
    read(new_socket,buffer,sizeof(buffer));
    printf("Message:%s",buffer);
    send(new_socket,"Hello from Server",17,0);
    close(new_socket);
    close(sock_fd);
    return 0;
}
