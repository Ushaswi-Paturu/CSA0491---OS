#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

int findOptimalPage(int pages[], int frames[], int n, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < MAX_FRAMES; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void optimal(int pages[], int n) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;

    printf("Optimal Page Replacement Algorithm Simulation\n");
    printf("Page Reference String: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n\n");

    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1; // Initialize all frames to -1 (indicating no page loaded)
    }

    for (int i = 0; i < n; i++) {
        printf("Referencing page %d\n", pages[i]);
        int pageFound = 0;

        // Check if page already in memory
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == pages[i]) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            printf("Page fault occurred, loading page %d into memory\n", pages[i]);
            int index = findOptimalPage(pages, frames, n, i + 1);
            frames[index] = pages[i]; // Load the new page into the optimal frame
            pageFaults++;
            printf("Current memory state: ");
            for (int k = 0; k < MAX_FRAMES; k++) {
                printf("%d ", frames[k]);
            }
            printf("\n");
        } else {
            printf("Page %d already in memory, no page fault\n", pages[i]);
        }
    }

    printf("\nTotal page faults: %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES] = {1, 2, 3, 4, 5, 1, 6, 7, 8, 2, 9, 1, 4, 5, 6, 7, 8, 9, 1, 2};
    int n = sizeof(pages) / sizeof(pages[0]);

    optimal(pages, n);

    return 0;
}

