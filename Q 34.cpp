#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1000
#define MAX_RECORD_SIZE 100

char file[MAX_FILE_SIZE]; // Array to represent the file
int filePointer = 0; // Pointer to the next available position in the file

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

void displayFileContents() {
    printf("File Contents:\n");
    printf("%s\n", file);
}

int main() {
    // Add records to the file
    addRecord("Record 1: This is the first record.");
    addRecord("Record 2: This is the second record.");
    addRecord("Record 3: This is the third record.");

    // Display the contents of the file
    displayFileContents();

    return 0;
}

