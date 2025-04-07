#include <stdio.h>

int main() {
    int bucket_size, n, outgoing, incoming, store = 0;
    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);
    printf("Enter outgoing rate: ");
    scanf("%d", &outgoing);
    printf("Enter number of inputs: ");
    scanf("%d", &n);

    while(n != 0) {
        printf("\nEnter incoming packet size: ");
        scanf("%d", &incoming);
        printf("Incoming packet size: %d\n", incoming);

        if(incoming <= (bucket_size - store)) {
            store += incoming;
            printf("Bucket buffer size: %d out of %d\n", store, bucket_size);
        } else {
            printf("Dropped %d packet(s)\n", incoming - (bucket_size - store));
            store = bucket_size;
            printf("Bucket buffer size: %d out of %d\n", store, bucket_size);
        }
        store -= outgoing;
        if(store < 0) store = 0;
        printf("After outgoing, %d packet(s) left in buffer\n", store);
        n--;
    }
    return 0;
}
