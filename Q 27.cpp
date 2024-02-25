#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

void file_management_operations() {
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
}

void ls_unix_command() {
    DIR *dir;
    struct dirent *entry;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // Read directory entries
    printf("Contents of current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);
}

int main() {
    printf("----- File Management Operations -----\n");
    file_management_operations();
    
    printf("\n\n----- ls UNIX Command Simulation -----\n");
    ls_unix_command();

    return 0;
}

