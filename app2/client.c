#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int client_socket;
    struct sockaddr_in client;
    int number;
    char responses[1024]={0};
    char buffer[1024]={0};
    client_socket = socket(AF_INET,SOCK_STREAM,0);
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(8080);
    printf("Enter the Number:\n");
    scanf("%s",buffer);
    connect(client_socket,(struct sockaddr*)&client,sizeof(client));
    send(client_socket,buffer,strlen(buffer),0);
    read(client_socket,responses,sizeof(responses));
    printf("%s\n",responses);
    close(client_socket);
    return 0;
}