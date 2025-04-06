#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int ack() { return rand() % 2; }

int main() {
    int n, ws, wt, i = 1;
    srand(time(0));
    printf("Packets to send: "); scanf("%d", &n);
    printf("Window size: "); scanf("%d", &ws);
    printf("Wait time: "); scanf("%d", &wt);

    while (i <= n) {
        printf("Sending packets %d to %d...\n", i, i+ws-1); sleep(1);
        if (ack()) printf("ACK received for packet %d\n\n", i++);
        else { 
          printf("ACK lost for packet %d! Resending window after %d sec...\n\n", i, wt);
          sleep(wt); 
        }
    }
    printf("All packets sent!\n"); return 0;
}
