#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 1000

// Function to simulate FCFS disk scheduling
int fcfs(int diskQueue[], int n, int head) {
    int totalHeadMovement = 0;

    // Service requests in the order they arrive
    for (int i = 0; i < n; i++) {
        totalHeadMovement += abs(diskQueue[i] - head); // Calculate head movement
        head = diskQueue[i]; // Move head to the next request
    }

    return totalHeadMovement;
}

int main() {
    int n; // Number of disk queue requests
    int head; // Current disk head position
    int diskQueue[MAX_REQUESTS]; // Array to store disk queue requests

    // Input disk queue requests
    printf("Enter the number of disk queue requests: ");
    scanf("%d", &n);

    printf("Enter the disk queue requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &diskQueue[i]);
    }

    // Input current disk head position
    printf("Enter the current disk head position: ");
    scanf("%d", &head);

    // Simulate FCFS disk scheduling and calculate total head movement
    int totalHeadMovement = fcfs(diskQueue, n, head);

    // Output the total head movement
    printf("Total head movement using FCFS: %d\n", totalHeadMovement);

    return 0;
}

