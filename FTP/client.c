#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 100

int main() {
    int serverSocket, n;
    struct sockaddr_in server;
    char filename[MAX], recvline[MAX];

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    connect(serverSocket, (struct sockaddr*)&server, sizeof(server));

    printf("Enter the source file name: ");
    scanf("%s", filename);

    send(serverSocket, filename, strlen(filename),0);

    printf("File content received:\n");
    while ((recv(serverSocket,recvline,MAX,0)) > 0) {
        printf("%s", recvline);
    }
    close(serverSocket);
    return 0;
}
