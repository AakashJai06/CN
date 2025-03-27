#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>  

int main() {
    char buffer[100];
    int k; // Error Flag
    int sock_desc;
    struct sockaddr_in server;

    /* Creating Socket */
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) {
        printf("Error In Socket Creation!\n");
        return 1;
    }
    printf("Socket Created Successfully!\n");

    server.sin_family = AF_INET;
    server.sin_port = htons(3003);  
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  

    /* Connecting Process */
    k = connect(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1) {
        printf("Error In Connecting To The Server!\n");
        return 1;
    }
    printf("Connection Successful!\n");

    /* Data Sending Process */
    printf("\nEnter The Data To Be Sent: ");
    fgets(buffer, 100, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; 

    k = send(sock_desc, buffer, strlen(buffer), 0);
    if (k == -1) {
        printf("Error In Sending Data!\n");
        return 1;
    }
    printf("Message Sent!\n");

    close(sock_desc);

    return 0;
}
