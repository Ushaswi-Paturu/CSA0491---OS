#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 1000

// Function to simulate SCAN disk scheduling
int scan(int diskQueue[], int n, int head, int direction, int totalTracks) {
    int totalHeadMovement = 0;
    int visited[totalTracks + 1]; // Array to mark visited tracks
    int currentTrack = head; // Start at the current head position

    // Initialize visited array
    for (int i = 0; i <= totalTracks; i++) {
        visited[i] = 0;
    }

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

    // SCAN towards the end
    if (direction == 1) {
        for (int i = head; i <= totalTracks; i++) {
            if (visited[i] == 0) {
                totalHeadMovement += abs(i - currentTrack);
                currentTrack = i;
                visited[i] = 1;
            }
        }

        // Change direction and scan towards the beginning
        for (int i = totalTracks; i >= 0; i--) {
            if (visited[i] == 0) {
                totalHeadMovement += abs(i - currentTrack);
                currentTrack = i;
                visited[i] = 1;
            }
        }
    }
    // SCAN towards the beginning
    else {
        for (int i = head; i >= 0; i--) {
            if (visited[i] == 0) {
                totalHeadMovement += abs(i - currentTrack);
                currentTrack = i;
                visited[i] = 1;
            }
        }

        // Change direction and scan towards the end
        for (int i = 0; i <= totalTracks; i++) {
            if (visited[i] == 0) {
                totalHeadMovement += abs(i - currentTrack);
                currentTrack = i;
                visited[i] = 1;
            }
        }
    }

    return totalHeadMovement;
}

int main() {
    int n; // Number of disk queue requests
    int head; // Current disk head position
    int direction; // Direction of scanning (1 for towards the end, 0 for towards the beginning)
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

    // Input direction of scanning
    printf("Enter the direction of scanning (1 for towards the end, 0 for towards the beginning): ");
    scanf("%d", &direction);

    // Input total number of tracks on the disk
    printf("Enter the total number of tracks on the disk: ");
    scanf("%d", &totalTracks);

    // Simulate SCAN disk scheduling and calculate total head movement
    int totalHeadMovement = scan(diskQueue, n, head, direction, totalTracks);

    // Output the total head movement
    printf("Total head movement using SCAN: %d\n", totalHeadMovement);

    return 0;
}

