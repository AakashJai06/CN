#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8000

typedef struct packet {
    char data[1024];
} Packet;

typedef struct frame {
    int frame_kind; // 1 = data, 0 = ack
    int sq_no;
    int ack;
    Packet packet;
} Frame;

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t addr_size = sizeof(servaddr);
    Frame frame_send, frame_recv;
    int frame_id = 0, ack_received = 1;
    char input[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    while (1) {
        if (ack_received) {
            printf("Enter data to send: ");
            scanf("%s", input);

            frame_send.frame_kind = 1;
            frame_send.sq_no = frame_id;
            frame_send.ack = 0;
            strcpy(frame_send.packet.data, input);

            sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&servaddr, addr_size);
            printf("[+] Frame Sent (ID: %d)\n", frame_id);
        }

        int recv_len = recvfrom(sockfd, &frame_recv, sizeof(Frame), 0, (struct sockaddr*)&servaddr, &addr_size);
        if (recv_len > 0 && frame_recv.frame_kind == 0 && frame_recv.ack == frame_id + 1) {
            printf("[+] ACK Received for Frame %d\n\n", frame_id);
            ack_received = 1;
            frame_id++;
        } else {
            printf("[-] ACK Not Received. Retransmitting Frame %d\n", frame_id);
            ack_received = 0;
        }
    }

    close(sockfd);
    return 0;
}
