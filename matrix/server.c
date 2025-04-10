#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sock_fd,client_socket,n;
    struct sockaddr_in server,client;
    socklen_t len = sizeof(client);
    char size[1024];
    int buffer[1024][1024];
    char response[1024];
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
    bind(sock_fd,(struct sockaddr*)&server,sizeof(server));
    listen(sock_fd,5);
    printf("Server:Server is listening at port 8080\n");
    client_socket = accept(sock_fd,(struct sockaddr*)&client,&len);
    read(client_socket,&n,sizeof(int));
    read(client_socket,buffer,sizeof(buffer));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d\t",buffer[i][j]);
        }
        printf("\n");
    }
    close(client_socket);
    close(sock_fd);
    return 0;
}