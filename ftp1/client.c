#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int client_socket;
    struct sockaddr_in client;
    char buffer[1024];
    char response[1024];
    client_socket = socket(AF_INET,SOCK_STREAM,0);
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(8080);
    connect(client_socket,(struct sockaddr*)&client,sizeof(client));
    printf("Enter the filename:\n");
    scanf("%s",buffer);
    send(client_socket,buffer,strlen(buffer),0);
    int bytes_received = read(client_socket, response, sizeof(response) - 1); // Leave space for null-terminator
    if (bytes_received > 0) {
        response[bytes_received] = '\0'; // Null-terminate the response
        printf("Server: %s\n", response); // Print the server's message
    }
    close(client_socket);
    return 0;
}