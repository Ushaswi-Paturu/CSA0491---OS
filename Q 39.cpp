#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 1000

// Function to simulate C-SCAN disk scheduling
int cScan(int diskQueue[], int n, int head, int totalTracks) {
    int totalHeadMovement = 0;
    int currentTrack = head;

    // Sort disk queue requests
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (diskQueue[i] > diskQueue[j]) {
                int temp = diskQueue[i];
                diskQueue[i] = diskQueue[j];
                diskQueue[j] = temp;
            }
        }
    }

    // Scan towards the end
    for (int i = head; i <= totalTracks; i++) {
        totalHeadMovement += abs(i - currentTrack);
        currentTrack = i;
    }

    // Wrap around and scan towards the beginning
    totalHeadMovement += abs(totalTracks - currentTrack);
    currentTrack = 0;

    for (int i = 0; i < head; i++) {
        totalHeadMovement += abs(i - currentTrack);
        currentTrack = i;
    }

    return totalHeadMovement;
}

int main() {
    int n; // Number of disk queue requests
    int head; // Current disk head position
    int totalTracks; // Total number of tracks on the disk
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

    // Input total number of tracks on the disk
    printf("Enter the total number of tracks on the disk: ");
    scanf("%d", &totalTracks);

    // Simulate C-SCAN disk scheduling and calculate total head movement
    int totalHeadMovement = cScan(diskQueue, n, head, totalTracks);

    // Output the total head movement
    printf("Total head movement using C-SCAN: %d\n", totalHeadMovement);

    return 0;
}

