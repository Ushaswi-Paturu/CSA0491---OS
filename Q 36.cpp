#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 100
#define MAX_BLOCKS 10
#define MAX_FILES 5

// Structure to represent a disk block
typedef struct DiskBlock {
    char data[BLOCK_SIZE];
    struct DiskBlock *next;
} DiskBlock;

// Structure to represent a file
typedef struct File {
    DiskBlock *firstBlock;
    DiskBlock *lastBlock;
} File;

File directory[MAX_FILES]; // Directory containing pointers to the first and last blocks of each file

// Function to add a record to a file
void addRecord(File *file, char record[]) {
    DiskBlock *newBlock = (DiskBlock *)malloc(sizeof(DiskBlock));
    if (newBlock == NULL) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    strncpy(newBlock->data, record, strlen(record));
    newBlock->next = NULL;

    if (file->firstBlock == NULL) {
        file->firstBlock = newBlock;
    } else {
        file->lastBlock->next = newBlock;
    }
    file->lastBlock = newBlock;
    printf("Record \"%s\" added successfully\n", record);
}

// Function to display all records in a file
void displayFileContents(File *file) {
    DiskBlock *currentBlock = file->firstBlock;
    printf("File Contents:\n");
    while (currentBlock != NULL) {
        printf("%s\n", currentBlock->data);
        currentBlock = currentBlock->next;
    }
}

int main() {
    // Initialize directory
    for (int i = 0; i < MAX_FILES; i++) {
        directory[i].firstBlock = NULL;
        directory[i].lastBlock = NULL;
    }

    // Add records to files
    addRecord(&directory[0], "Record 1: This is the first record of File 1");
    addRecord(&directory[0], "Record 2: This is the second record of File 1");
    addRecord(&directory[1], "Record 1: This is the first record of File 2");
    addRecord(&directory[1], "Record 2: This is the second record of File 2");
    addRecord(&directory[1], "Record 3: This is the third record of File 2");

    // Display contents of files
    displayFileContents(&directory[0]);
    displayFileContents(&directory[1]);

    // Free allocated memory
    for (int i = 0; i < MAX_FILES; i++) {
        DiskBlock *currentBlock = directory[i].firstBlock;
        while (currentBlock != NULL) {
            DiskBlock *temp = currentBlock;
            currentBlock = currentBlock->next;
            free(temp);
        }
    }

    return 0;
}

