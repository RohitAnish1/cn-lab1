#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int client_socket;
    struct sockaddr_in client;
    char responses[1024] = {0};
    char buffer[1024] = {0};
    char special[2]; // Char array to hold the special character and null terminator

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(8081);

    printf("Enter the String:\n");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the Symbol:\n");
    fgets(special, sizeof(special), stdin);
    special[strcspn(special, "\n")] = '\0'; // Remove trailing newline

    connect(client_socket, (struct sockaddr*)&client, sizeof(client));

    int msg_len = strlen(buffer);
    send(client_socket, &msg_len, sizeof(msg_len), 0); // Send the length of the string
    send(client_socket, buffer, msg_len, 0);          // Send the string
    send(client_socket, special, sizeof(special), 0); // Send the special character as a char array

    read(client_socket, responses, sizeof(responses));
    printf("The corrected string is: %s\n", responses);

    close(client_socket);
    return 0;
}