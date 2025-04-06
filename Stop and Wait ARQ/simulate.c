#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int ack() { return rand() % 2; }

int main() {
    int n, wt, i = 1;
    printf("Enter number of packets to send: "); scanf("%d", &n);
    printf("Enter waiting time in seconds before retransmission: "); scanf("%d", &wt);
    srand(time(0));

    while (i <= n) {
        printf("Sending packet %d...\n", i); sleep(1);
        if (ack()) printf("ACK received for packet %d\n\n", i++);
        else {
          printf("ACK lost for packet %d, Retransmitting after %d seconds...\n\n", i, wt); 
          sleep(wt); }
    }
    printf("All packets sent successfully!\n"); return 0;
}
