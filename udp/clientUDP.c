#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE] = "Hello from client";
    char response[BUFFER_SIZE];
    socklen_t len = sizeof(server);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address configuration
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address (localhost)

    // Send message to server
    sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&server, len);
    printf("Message sent to server\n");

    // Receive response from server
    memset(response, 0, BUFFER_SIZE);
    recvfrom(sockfd, response, BUFFER_SIZE, 0, (struct sockaddr *)&server, &len);
    printf("Message from server: %s\n", response);

    close(sockfd);
    return 0;
}
