// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int c_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server = {0};

    server.sin_family = AF_INET;
    server.sin_port = htons(9009);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(c_sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
        perror("Connection failed");
        return 1;
    }

    printf("Client with individual acknowledgment scheme\n");

    char buffer[100], ack_msg[50] = "acknowledgementof-";
    for (int i = 0; i < 10; i++) {
        if (i == 8) {
            printf("Simulating loss at %d\n", i);
            read(c_sock, buffer, sizeof(buffer));
            continue; // Skip ack to simulate loss
        }

        read(c_sock, buffer, sizeof(buffer));
        if (buffer[strlen(buffer) - 1] != i + '0') {
            printf("Out of order, discarded: %s\n", buffer);
            i--; // Stay on same packet
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
