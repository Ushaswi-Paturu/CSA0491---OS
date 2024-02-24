#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    char buffer[100];
    ssize_t num_bytes;

    // Create a new file
    fd = creat("example.txt", 0644);
    if (fd == -1) {
        perror("creat");
        exit(EXIT_FAILURE);
    }
    printf("File created successfully.\n");

    // Open the file in write-only mode
    fd = open("example.txt", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write to the file
    if (write(fd, "Hello, World!\n", 14) != 14) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    printf("Data written to the file.\n");

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    // Open the file in read-only mode
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read from the file
    num_bytes = read(fd, buffer, sizeof(buffer));
    if (num_bytes == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    printf("Data read from the file: %.*s", (int)num_bytes, buffer);

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}

