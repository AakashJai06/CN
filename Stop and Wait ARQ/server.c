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
    struct sockaddr_in servaddr, cliaddr;
    socklen_t addr_size = sizeof(cliaddr);
    Frame frame_recv, frame_send;
    int expected_frame = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    while (1) {
        int recv_len = recvfrom(sockfd, &frame_recv, sizeof(Frame), 0,
                                (struct sockaddr*)&cliaddr, &addr_size);

        if (recv_len > 0 && frame_recv.frame_kind == 1 && frame_recv.sq_no == expected_frame) {
            printf("[+] Frame Received: %s\n", frame_recv.packet.data);

            frame_send.frame_kind = 0;
            frame_send.sq_no = 0;
            frame_send.ack = expected_frame + 1;

            sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&cliaddr, addr_size);
            printf("[+] ACK Sent for Frame %d\n", expected_frame);
            expected_frame++;
        } else {
            printf("[-] Frame not valid or out of order\n");
        }
    }

    close(sockfd);
    return 0;
}
