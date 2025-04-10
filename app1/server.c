#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sock_fd,client_socket;
    struct sockaddr_in server,client;
    socklen_t len = sizeof(client);
    char *numbers[]={"Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine"};
    char buffer[1024],result[1024]="";
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
    bind(sock_fd,(struct sockaddr*)&server,sizeof(server));
    listen(sock_fd,3);
    printf("Server:Listening for Connections\n");
    client_socket = accept(sock_fd,(struct sockaddr*)&client,&len);
    read(client_socket,buffer,sizeof(buffer));
    for(int i=0;i<strlen(buffer);i++){
    if(buffer[i]>='0'&& buffer[i]<='9'){
        strcat(result,numbers[buffer[i]-'0']);
        strcat(result," ");
    }
    }
    send(client_socket,result,strlen(result),0);
    close(sock_fd);
    close(client_socket);
}
