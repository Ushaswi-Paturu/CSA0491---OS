#include <stdio.h>

#define MAX_BLOCKS 100

int main() {
    int memory_blocks[MAX_BLOCKS];
    int num_blocks;
    int process_size;
    int i, j;
    int min_fragment = __INT_MAX__;
    int allocated_block = -1;

    // Input number of memory blocks
    printf("Enter number of memory blocks: ");
    scanf("%d", &num_blocks);

    // Input memory block sizes
    printf("Enter size of each memory block:\n");
    for (i = 0; i < num_blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &memory_blocks[i]);
    }

    // Input size of process
    printf("Enter size of process: ");
    scanf("%d", &process_size);

    // Find best fit
    for (i = 0; i < num_blocks; i++) {
        if (memory_blocks[i] >= process_size) {
            if (memory_blocks[i] - process_size < min_fragment) {
                min_fragment = memory_blocks[i] - process_size;
                allocated_block = i;
            }
        }
    }

    // Allocate memory if a block is found
    if (allocated_block != -1) {
        printf("Memory allocated successfully to process with size %d in block %d.\n", process_size, allocated_block + 1);
    } else {
        printf("No suitable block found for memory allocation.\n");
    }

    return 0;
}

