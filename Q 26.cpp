#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";
    char text_to_write[] = "Hello, this is a test!";
    char text_read[100]; // Assuming maximum line length is 100 characters

    // Creating a file and writing to it
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", text_to_write);
    fclose(file);
    printf("File \"%s\" created and written successfully.\n", filename);

    // Opening the file for reading
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Reading from the file
    printf("Contents of file \"%s\":\n", filename);
    fgets(text_read, sizeof(text_read), file);
    printf("%s", text_read);
    fclose(file);

    return 0;
}

