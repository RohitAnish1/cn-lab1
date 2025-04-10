#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int isPrime(int n) {
    if (n <= 1) {
        return 0; // Numbers <= 1 are not prime
    }
    for (int i = 2; i * i <= n; i++) { // Check divisors up to sqrt(n)
        if (n % i == 0) {
            return 0; // Not prime if divisible by i
        }
    }
    return 1; // Prime if no divisors found
}

int main(){
    int sock_fd,client_socket;
    struct sockaddr_in server,client;
    socklen_t len = sizeof(client);
    char buffer[1024]={0};
    int number;
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);
    bind(sock_fd,(struct sockaddr*)&server,sizeof(server));
    listen(sock_fd,3);
    printf("Server:Listening for Connections\n");
    client_socket = accept(sock_fd,(struct sockaddr*)&client,&len);
    read(client_socket,buffer,sizeof(buffer));
    number = atoi(buffer);
    if(isPrime(number)){
        send(client_socket,"Number is prime",sizeof("Number is prime"),0);
    }
    else{
        send(client_socket,"Number is not prime",sizeof("Number is not prime"),0);
    }
    close(sock_fd);
    close(client_socket);
}
