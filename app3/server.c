#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

void replace_special(char *str, char special) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == ' ') {
            str[i] = special; // Replace space with the special character
        }
    }
}

int main() {
    int sock_fd, client_socket;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024] = {0};
    char special[2]; // Char array to hold the special character and null terminator
    int msg_len;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8081);

    bind(sock_fd, (struct sockaddr*)&server, sizeof(server));
    listen(sock_fd, 5);
    printf("Server: Server is listening\n");

    client_socket = accept(sock_fd, (struct sockaddr*)&client, &len);

    read(client_socket, &msg_len, sizeof(msg_len)); // Read the length of the string
    read(client_socket, buffer, msg_len);          // Read the string
    buffer[msg_len] = '\0';                        // Null-terminate the string
    read(client_socket, special, sizeof(special)); // Read the special character as a char array

    printf("Received string: %s\n", buffer);
    printf("Received special character: %s\n", special);

    replace_special(buffer, special[0]); // Use the first character of the array

    send(client_socket, buffer, strlen(buffer), 0); // Send the modified string back to the client

    close(client_socket);
    close(sock_fd);
    return 0;
}