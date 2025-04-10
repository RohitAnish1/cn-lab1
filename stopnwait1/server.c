#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int server_fd,new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    int ack_prob = 70;
    srand(time(0));
    //Create
    if((server_fd=socket(AF_INET,SOCK_STREAM,0))==0){
       perror("Socket Creation failed");
       exit(EXIT_FAILURE);
    }
    //server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    //bind the socket
    if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))==0){
        perror("Bind Failed");
        exit(EXIT_FAILURE);
    }
    if(listen(server_fd,3)<0){
        perror("Listen Failed");
        exit(EXIT_FAILURE);
    }
    printf("Server Waiting for Connections..\n");
    //accept client connection
    if((new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
        perror("Accept Failed");
        exit(EXIT_FAILURE);
    }
    printf("Server Connection Established");
    while(1){
        //Recieve packets from the client
        int valread = read(new_socket,buffer,BUFFER_SIZE);
        if(valread == 0) break;
        printf("Server Recieved Packet-%s\n",buffer);
        //Simulate ACK
        if(rand()%100<ack_prob){
            printf("ACK sent for package%s\n\n",buffer);
            send(new_socket,"ACK",strlen("ACK"),0);
        }
        else{
            printf("ACK lost for package%s\n\n",buffer);
        }
        memset(buffer,0,BUFFER_SIZE);
    }
        close(server_fd);
        close(new_socket);
}
