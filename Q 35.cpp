#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1000
#define BLOCK_SIZE 100
#define MAX_BLOCKS 10

char file[MAX_FILE_SIZE]; // Array to represent the file
char indexBlock[MAX_BLOCKS][BLOCK_SIZE]; // Index block containing pointers to each block of the file
int filePointer = 0; // Pointer to the next available position in the file
int indexPointer = 0; // Pointer to the next available position in the index block

void addRecord(char record[]) {
    int recordSize = strlen(record);
    if (filePointer + recordSize > MAX_FILE_SIZE) {
        printf("Error: Not enough space to add record\n");
        return;
    }
    strncpy(file + filePointer, record, recordSize);
    filePointer += recordSize;
    printf("Record \"%s\" added successfully\n", record);
}

void updateIndexBlock() {
    if (indexPointer >= MAX_BLOCKS) {
        printf("Error: Index block is full\n");
        return;
    }
    snprintf(indexBlock[indexPointer], sizeof(indexBlock[indexPointer]), "%d", filePointer);
    indexPointer++;
}

void displayFileContents() {
    printf("File Contents:\n");
    printf("%s\n", file);
}

void displayIndexBlock() {
    printf("Index Block Contents:\n");
    for (int i = 0; i < indexPointer; i++) {
        printf("Block %d: %s\n", i + 1, indexBlock[i]);
    }
}

int main() {
    // Add records to the file
    addRecord("Record 1: This is the first record.");
    updateIndexBlock();
    addRecord("Record 2: This is the second record.");
    updateIndexBlock();
    addRecord("Record 3: This is the third record.");
    updateIndexBlock();

    // Display the contents of the file and index block
    displayFileContents();
    displayIndexBlock();

    return 0;
}

