#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_MSG_SIZE 1024
#define SERVER_IP "192.168.7.34"
#define PORT 8081

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[MAX_MSG_SIZE];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server on %s:%d\n", SERVER_IP, PORT);

    while (1) {
        printf("Enter your message: ");
        fgets(buffer, MAX_MSG_SIZE, stdin);

        // Send message to server
        send(client_socket, buffer, strlen(buffer), 0);

        // Receive echo from server
        int bytes_received = recv(client_socket, buffer, MAX_MSG_SIZE, 0);
        if (bytes_received < 0) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        buffer[bytes_received] = '\0';
        printf("Echo from server: %s\n", buffer);
    }

    // Close socket
    close(client_socket);

    return 0;
}

