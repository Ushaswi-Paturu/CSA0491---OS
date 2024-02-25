#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    // Open a directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Name: %s\n", entry->d_name);

        // Get file information using stat
        struct stat file_stat;
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("Error getting file status");
            continue;
        }
        printf("File Size: %ld bytes\n", file_stat.st_size);
        printf("File Inode: %ld\n", file_stat.st_ino);

        // Demonstrate file seeking using lseek
        int file = open(entry->d_name, O_RDONLY);
        if (file == -1) {
            perror("Error opening file");
            continue;
        }

        off_t current_pos = lseek(file, 0, SEEK_CUR);
        if (current_pos == -1) {
            perror("Error seeking file");
            close(file);
            continue;
        }

        printf("Current File Offset: %lld\n", (long long)current_pos);

        // Move file pointer to the end of the file
        off_t end_pos = lseek(file, 0, SEEK_END);
        if (end_pos == -1) {
            perror("Error seeking file");
            close(file);
            continue;
        }

        printf("End File Offset: %lld\n", (long long)end_pos);

        // Close the file
        close(file);
    }

    // Close the directory
    closedir(dir);

    return 0;
}

