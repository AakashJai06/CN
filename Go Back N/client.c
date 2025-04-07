// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9009
#define MAX_MSGS 10
#define LOSS_INDEX 8

int main() {
    int c_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server = {0};

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(c_sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
        perror("Connection failed");
        return 1;
    }

    printf("Client with individual acknowledgment scheme\n");

    char buffer[100], ack_msg[50] = "acknowledgementof-";

    for (int i = 0; i < MAX_MSGS; i++) {
        read(c_sock, buffer, sizeof(buffer));

        if (i == LOSS_INDEX) {
            printf("Simulating loss at %d\n", i);
            continue; // Skip ACK to simulate loss
        }

        if (buffer[strlen(buffer) - 1] != i + '0') {
            printf("Out of order, discarded: %s\n", buffer);
            i--; // Retry same packet
            continue;
        }

        printf("Received: %s\n", buffer);
        char ack[60];
        sprintf(ack, "%s%d", ack_msg, i);
        write(c_sock, ack, sizeof(ack));
    }

    close(c_sock);
    return 0;
}
