#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char filename[BUFFER_SIZE], buffer[BUFFER_SIZE];
    FILE *file;
    socklen_t len = sizeof(clientAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);
    printf("Waiting for client...\n");

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &len);
    printf("Client connected!\n");

    recv(clientSocket, filename, BUFFER_SIZE, 0);
    printf("Requested file: %s\n", filename);

    file = fopen(filename, "r");
    if (!file) {
        printf("File not found!\n");
        sprintf(buffer, "ERROR: File not found.\n");
        send(clientSocket, buffer, strlen(buffer), 0);
    } else {
        while (fgets(buffer, BUFFER_SIZE, file)) {
            send(clientSocket, buffer, strlen(buffer), 0);
            usleep(10000); 
        }
        fclose(file);
    }

    printf("File transfer complete.\n");
    close(clientSocket);
    close(serverSocket);
    return 0;
}
