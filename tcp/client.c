#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sock_fd;
    struct sockaddr_in server;
    char buffer[1024]={"Hello from Client"};
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
    connect(sock_fd,(struct sockaddr*)&server,sizeof(server));
    send(sock_fd,buffer,strlen(buffer),0);
    read(sock_fd,buffer,sizeof(buffer));
    printf("Response:%s",buffer);
    close(sock_fd);
    return 0;
}
