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
    char response[1024];
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
    bind(sock_fd,(struct sockaddr*)&server,sizeof(server));
    listen(sock_fd,5);
    printf("Server:Server is listening at port 8080\n");
    client_socket = accept(sock_fd,(struct sockaddr*)&client,&len);
    read(client_socket,buffer,sizeof(buffer));
    printf("Filename is:%s\n",buffer);
    FILE *file = fopen(buffer,"r");
    while(fgets(response,sizeof(response),file) != NULL){
    send(client_socket,response,strlen(response),0);
    memset(response,0,sizeof(response));
    }
    close(client_socket);
    close(sock_fd);
    return 0;
}