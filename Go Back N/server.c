// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define PORT 9009
#define MAX_MSGS 10
#define WINDOW_SIZE 3

int main() {
    int s_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server = {0}, client;
    socklen_t len = sizeof(client);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s_sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
        perror("Bind failed");
        return 1;
    }

    listen(s_sock, 5);
    printf("Server Up\nGo-Back-N (n=%d) used to send %d messages\n", WINDOW_SIZE, MAX_MSGS);

    int c_sock = accept(s_sock, (struct sockaddr*)&client, &len);
    if (c_sock < 0) {
        perror("Accept failed");
        return 1;
    }

    char msg[50] = "server message :";
    char buffer[50], ack[50];
    int i = 0;

    while (i < MAX_MSGS) {
        for (int j = 0; j < WINDOW_SIZE && i + j < MAX_MSGS; j++) {
            sprintf(buffer, "%s%d", msg, i + j);
            printf("Sent: %s\n", buffer);
            write(c_sock, buffer, sizeof(buffer));
            usleep(50000); // 50ms for clarity
        }

        fd_set fds;
        struct timeval timeout = {2, 0};
        FD_ZERO(&fds);
        FD_SET(c_sock, &fds);

        int ret = select(c_sock + 1, &fds, NULL, NULL, &timeout);
        if (ret == 0) {
            printf("Timeout: Resending from %d\n", i);
            continue;
        }

        for (int j = 0; j < WINDOW_SIZE && i < MAX_MSGS; j++, i++) {
            bzero(ack, sizeof(ack));
            read(c_sock, ack, sizeof(ack));
            printf("Ack: %s\n", ack);
        }
    }

    close(c_sock);
    close(s_sock);
    return 0;
}
