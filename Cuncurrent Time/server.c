// Server Code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the address
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is running and waiting for time requests on port %d...\n", PORT);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        // Receive message from client
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (n < 0) {
            perror("Receive failed");
            continue;
        }

        printf("Received request from client: %s\n", inet_ntoa(client_addr.sin_addr));

        // Get the current time
        time_t current_time = time(NULL);
        char *time_str = ctime(&current_time);

        // Send the current time back to the client
        sendto(sockfd, time_str, strlen(time_str), 0, (struct sockaddr *)&client_addr, addr_len);
        printf("Sent time to client: %s", time_str);
    }

    close(sockfd);
    return 0;
}
